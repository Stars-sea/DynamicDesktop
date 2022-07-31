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

	inline const wchar_t* WStringConvertToPtr(const std::wstring str)
	{
		if (str.empty()) return NULL;
		return str.c_str();
	}

	template <typename T>
	concept is_char_ele = std::_Is_any_of_v<T, char, wchar_t>;

	template <is_char_ele Ele>
	std::basic_string<Ele> HandleToString(const size_t& handle)
	{
		using namespace std;
		basic_stringstream<Ele> ss;
		ss	<< setiosflags(ios::right)
			<< setw(16)
			<< setfill<Ele>('0')
			<< hex
			<< handle;
		return ss.str();
	}
}

export class invaild_handle : public std::exception
{
public:
	invaild_handle(size_t handle) : 
		handle(handle), std::exception(("Invaild handle " + Utils::HandleToString<char>(handle)).c_str()) {}
private:
	const size_t handle;
};

export class WindowHandle
{
private:
	typedef std::unique_ptr<WindowHandle> ptr_type;

	HWND const hWnd;

	static std::list<WindowHandle> instances;

	void ValidAndThrow() const
	{
		if (!Valid()) {
			instances.remove(*this);
			throw invaild_handle(hId);
		}
	}

public:
	const size_t hId;

	WindowHandle(const HWND& hWnd) :
		hWnd(hWnd), hId(size_t(hWnd)) { }

	WindowHandle(const size_t& hId) :
		hWnd(HWND(hId)), hId(hId) { }

	WindowHandle(const std::wstring& className, const std::wstring& windowName) : 
		WindowHandle(FindWindow(
			Utils::WStringConvertToPtr(className),
			Utils::WStringConvertToPtr(windowName)
		)) {}

	~WindowHandle() { instances.remove(*this); }

	bool Valid() const { return IsWindow(hWnd); }

	bool Cover() const
	{
		ValidAndThrow();

		HWND hProgman  = Utils::GetProgmanHWND();
		HWND hWorkerW2 = Utils::GetDesktopWorkerW2();

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

		ValidAndThrow();
		SetParent(hWnd, NULL);
	}

	bool IsCovered() const
	{
		ValidAndThrow();
		return GetParent(hWnd) == Utils::GetProgmanHWND();
	}

	bool operator==(const WindowHandle& other) const
	{
		if (this == &other) return true;
		if (hWnd == other.hWnd) return true;
		return false;
	}

	operator std::string()  const { return Utils::HandleToString<char>(hId); }
	operator std::wstring() const { return Utils::HandleToString<wchar_t>(hId); }
};

std::list<WindowHandle> WindowHandle::instances;
