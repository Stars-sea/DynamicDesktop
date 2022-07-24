#include "pch.h"
#include "CoverDesktop.h"

#include <string>
#include <exception>

using namespace DynamicDesktop::CoverDesktop;

#pragma region Utils
HWND Utils::GetProgmanHWND()
{
	return FindWindow(L"Progaman", NULL);
}

HWND Utils::GetDesktopWorkerW1() {
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

HWND Utils::GetDesktopWorkerW2() {
	HWND hWorkerW1 = GetDesktopWorkerW1();
	if (!IsWindow(hWorkerW1)) return NULL;

	HWND hWorkWWnd = FindWindowEx(0, hWorkerW1, L"WorkerW", NULL);
	return hWorkWWnd;
}

HWND Utils::GetHWNDFromPID(const DWORD pid) {
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
#pragma endregion


CoverDesktop CoverDesktop::GetInstance(const HWND hWnd)
{
	auto end = instances.end();
	auto cd = std::find_if(instances.begin(), end,
		[hWnd](CoverDesktop& cd1) -> bool {
			return cd1.hWnd == hWnd;
		});
	if (cd != end) return *cd;

	return CoverDesktop(hWnd);
}

CoverDesktop::CoverDesktop(const HWND hWnd) : hWnd(hWnd)
{
	if (!IsWindow(hWnd)) throw std::exception("Passed HWND is invaild");
	instances.push_front(*this);
}

CoverDesktop::~CoverDesktop()
{
	instances.remove(*this);
}

bool CoverDesktop::ValidHWND() const
{
	return IsWindow(hWnd);
}

bool CoverDesktop::Cover() const
{
	if (!ValidHWND())
		throw std::exception("Invalid HWND");

	HWND hProgman = Utils::GetProgmanHWND();
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

void CoverDesktop::Uncover() const {
	HWND hWorkerW2 = Utils::GetDesktopWorkerW2();
	if (IsWindow(hWorkerW2))
		ShowWindow(hWorkerW2, SW_SHOW);

	if (ValidHWND())
		SetParent(hWnd, NULL);
}

void CoverDesktop::UncoverAll()
{
	HWND hWorkerW2 = Utils::GetDesktopWorkerW2();
	if (IsWindow(hWorkerW2))
		ShowWindow(hWorkerW2, SW_SHOW);

	const auto end = instances.end();
	for (auto begin = instances.begin(); begin != end; ) {
		if (!begin->ValidHWND()) {
			instances.erase(begin++);
			continue;
		}
		SetParent(begin->hWnd, NULL);
		begin++;
	}
}

bool CoverDesktop::operator==(const CoverDesktop& other) const
{
	if (this == &other) return true;
	if (hWnd == other.hWnd) return true;
	return false;
}
