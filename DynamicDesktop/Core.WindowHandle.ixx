#include "pch.h"
#include <string>
#include <Windows.h>

export module DynamicDesktop.Core.Handle;
import DynamicDesktop.Core.HandleHelper;

export class NativeWindowHandle
{
private:
	HWND const hWnd;

public:
	const size_t hId;

	NativeWindowHandle(const HWND& hWnd) :
		hWnd(hWnd), hId(size_t(hWnd)) { }

	NativeWindowHandle(const size_t& hId) :
		hWnd(HWND(hId)), hId(hId) { }

	NativeWindowHandle(const std::wstring& name, bool isTitle) : 
		NativeWindowHandle(isTitle ? FindWindow(NULL, name.c_str()) :
					           FindWindow(name.c_str(), NULL)
	) { }

	bool Valid() const { return IsWindow(hWnd); }

	bool Cover() const
	{
		if (!Valid()) return false;

		HWND hProgman  = GetProgmanHWND();
		HWND hWorkerW2 = GetDesktopWorkerW2();

		if (!hWorkerW2)
			SendMessageTimeout(hProgman, 0x52C, NULL, NULL, NULL, 100, NULL);

		if (!SetParent(hWnd, hProgman))
			return false;

		hWorkerW2 = GetDesktopWorkerW2();
		if (hWorkerW2) {
			ShowWindow(hWorkerW2, SW_HIDE);
			return true;
		}

		Uncover();
		return false;
	}

	void Uncover() const
	{
		HWND hWorkerW2 = GetDesktopWorkerW2();
		if (IsWindow(hWorkerW2))
			ShowWindow(hWorkerW2, SW_SHOW);

		if (Valid()) SetParent(hWnd, NULL);
	}

	bool IsCovered() const
	{
		return Valid() && GetParent(hWnd) == GetProgmanHWND();
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

	bool operator==(const NativeWindowHandle& other) const
	{
		if (this == &other) return true;
		if (hWnd == other.hWnd) return true;
		return false;
	}

	operator std::string()  const { return "0x"  + HandleToString<char>(hId);    }
	operator std::wstring() const { return L"0x" + HandleToString<wchar_t>(hId); }
};
