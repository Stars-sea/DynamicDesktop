#include "pch.h"
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

export module DynamicDesktop.Core.HandleHelper;

struct PIDAndHWNDs
{
	DWORD pid;
	std::vector<HWND> hWnds;
};

export HWND GetProgmanHWND() { return FindWindow(L"Progaman", NULL); }

export HWND GetDesktopWorkerW1() {
	HWND hWork1 = NULL;
	EnumWindows(
		[](HWND hWnd, LPARAM lParam) -> BOOL {
			if (FindWindowEx(hWnd, NULL, L"SHELLDLL_DefView", NULL)) {
				wchar_t className[32];
				if (GetClassName(hWnd, className, 31) &&
					std::wstring(className) == L"WorkerW")
				{
					*(HWND*)lParam = hWnd;
					return FALSE;
				}
			}
			return TRUE;
		}, (LPARAM)&hWork1);
	return hWork1;
}

export HWND GetDesktopWorkerW2() {
	HWND hWorkerW1 = GetDesktopWorkerW1();
	if (!IsWindow(hWorkerW1)) return NULL;

	HWND hWorkWWnd = FindWindowEx(0, hWorkerW1, L"WorkerW", NULL);
	return hWorkWWnd;
}

export std::vector<HWND> GetHWNDsFromPID(const DWORD pid) {
	PIDAndHWNDs pah{ pid };
	EnumWindows(
		[](HWND hWnd, LPARAM lParam) -> BOOL {
			PIDAndHWNDs* pah = (PIDAndHWNDs*)lParam;

			DWORD pid;
			GetWindowThreadProcessId(hWnd, &pid);
			if (pah->pid == pid)
				pah->hWnds.push_back(hWnd);
			return TRUE;
		}, (LPARAM)&pah);
	return pah.hWnds;
}

export template <typename T>
concept is_char_ele = std::_Is_any_of_v<T, char, wchar_t>;

export template <is_char_ele Ele>
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
