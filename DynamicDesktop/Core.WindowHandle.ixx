#include "pch.h"
#include <functional>

#pragma warning(disable: 5201)    // 关闭声明模块置顶提示
export module DynamicDesktop.Core;
#pragma warning(default: 5201)

#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <exception>

namespace Utils {
	struct PIDAndHWND
	{
		DWORD pid;
		HWND hWnd;
	};

	HWND GetProgmanHWND() { return FindWindow(L"Progaman", NULL); }

	HWND GetDesktopWorkerW1() {
		HWND hWork1 = NULL;
		EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
			if (FindWindowEx(hWnd, NULL, L"SHELLDLL_DefView", NULL)) {
				wchar_t className[32];
				if (GetClassName(hWnd, className, 31) &&
					std::wstring(className) == L"WorkerW"
					) {
					*(HWND*)lParam = hWnd;
					return FALSE;
				}
			}
			return TRUE;
			}, (LPARAM)&hWork1);
		return hWork1;
	}

	HWND GetDesktopWorkerW2() {
		HWND hWorkerW1 = GetDesktopWorkerW1();
		if (!IsWindow(hWorkerW1)) return NULL;

		HWND hWorkWWnd = FindWindowEx(0, hWorkerW1, L"WorkerW", NULL);
		return hWorkWWnd;
	}

	HWND GetHWNDFromPID(const DWORD pid) {
		PIDAndHWND pah{ pid, NULL };
		EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
			PIDAndHWND pah = *((PIDAndHWND*)lParam);

			DWORD pid;
			GetWindowThreadProcessId(pah.hWnd, &pid);
			if (pah.pid == pid) {
				pah.hWnd = hWnd;
				return FALSE;
			}
			return TRUE;
			}, (LPARAM)&pah);
		return pah.hWnd;
	}
}

export class WindowHandle
{
private:
	typedef std::unique_ptr<WindowHandle> ptr_type;

	HWND const hWnd;

	static std::list<WindowHandle> instances;

	static bool TryFindInstance(
		const std::function<bool(const WindowHandle&)>& pred,
		ptr_type& out
	) {
		const auto end  = instances.end();
		const auto iter = std::find_if(instances.begin(), end, pred);
		if (end == iter) return false;

		out.reset(&(*iter));
		return true;
	}

public:
	const size_t hId;

	WindowHandle(const HWND& hWnd) :
		hWnd(hWnd), hId(size_t(hWnd)) { }

	WindowHandle(const size_t& hId) :
		hWnd(HWND(hId)), hId(hId) { }

	~WindowHandle() { instances.remove(*this); }

	bool Valid() const { return IsWindow(hWnd); }

	bool Cover() const
	{
		if (!Valid())
			throw std::exception("Invalid HWND");

		HWND hProgman  = Utils::GetProgmanHWND();
		HWND hWorkerW2 = Utils:: GetDesktopWorkerW2();

		if (!hWorkerW2)
			SendMessageTimeout(hProgman, 0x52C, NULL, NULL, NULL, 100, NULL);

		if (!SetParent(hWnd, hProgman))
			return false;

		hWorkerW2 = Utils::GetDesktopWorkerW2();
		if (hWorkerW2) {
			ShowWindow(hWorkerW2, SW_HIDE);
			return true;
		}

		Uncover();
		return false;
	}

	void Uncover() const
	{
		HWND hWorkerW2 = Utils::GetDesktopWorkerW2();
		if (IsWindow(hWorkerW2))
			ShowWindow(hWorkerW2, SW_SHOW);

		if (Valid())
			SetParent(hWnd, NULL);
	}

	static void UncoverAll()
	{
		HWND hWorkerW2 = Utils::GetDesktopWorkerW2();
		if (IsWindow(hWorkerW2))
			ShowWindow(hWorkerW2, SW_SHOW);

		const auto end = instances.end();
		for (auto begin = instances.begin(); begin != end; ) {
			if (!begin->Valid()) {
				instances.erase(begin++);
				continue;
			}
			SetParent(begin->hWnd, NULL);
			begin++;
		}
	}

	bool operator==(const WindowHandle& other) const
	{
		if (this == &other) return true;
		if (hWnd == other.hWnd) return true;
		return false;
	}

	operator std::string() const
	{
		std::stringstream ss;
		ss << std::hex << hId;
		return ss.str();
	}

	operator std::wstring() const
	{
		std::wstringstream wss;
		wss << std::hex << hId;
		return wss.str();
	}
};

std::list<WindowHandle> WindowHandle::instances;
