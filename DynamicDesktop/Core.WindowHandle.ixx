#include "pch.h"

#pragma warning(disable: 5201)    // 关闭声明模块置顶提示
export module DynamicDesktop.Core;
#pragma warning(default: 5201)

#include <list>
#include <string>
#include <sstream>
#include <Windows.h>

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
			<< hex << uppercase
			<< handle;
		return ss.str();
	}
}

export class WindowHandle
{
private:
	HWND const hWnd;

public:
	const size_t hId;

	WindowHandle(const HWND& hWnd) :
		hWnd(hWnd), hId(size_t(hWnd)) { }

	WindowHandle(const size_t& hId) :
		hWnd(HWND(hId)), hId(hId) { }

	WindowHandle(const std::wstring& name, bool isTitle) : 
		WindowHandle(isTitle ? FindWindow(NULL, name.c_str()) :
					           FindWindow(name.c_str(), NULL)
	) { }

	bool Valid() const { return IsWindow(hWnd); }

	bool Cover() const
	{
		if (!Valid()) return false;

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

		if (Valid()) SetParent(hWnd, NULL);
	}

	bool IsCovered() const
	{
		return Valid() && GetParent(hWnd) == Utils::GetProgmanHWND();
	}

	std::wstring GetWindowTitle() const
	{
		if (!Valid()) return L"Invalid HWND 0x" + std::wstring(*this);

		wchar_t str[128];
		GetWindowText(hWnd, str, sizeof(str));
		return std::wstring(str);
	}

	std::wstring GetWindowClass() const
	{
		if (!Valid()) return L"Invalid HWND 0x" + std::wstring(*this);

		wchar_t str[128];
		RealGetWindowClass(hWnd, str, sizeof(str));
		return std::wstring(str);
	}

	HICON GetWindowIcon() const
	{
		if (!Valid()) return nullptr;

		return (HICON)GetClassLongPtr(hWnd, GCLP_HICON);
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
