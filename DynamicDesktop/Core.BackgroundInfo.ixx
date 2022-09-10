#include "pch.h"
#include <string>

export module DynamicDesktop.Core.BackgroundInfo;
import DynamicDesktop.Core.Handle;
import DynamicDesktop.Core.HandleHelper;

export class INativeBackgroundInfo
{
protected:
	INativeBackgroundInfo() = default;

public:
	virtual NativeWindowHandle GetHandle() = 0;
	virtual bool IsAvailable() { return GetHandle().Valid(); }
	virtual std::wstring GetDetails() {
		NativeWindowHandle handle = GetHandle();
		return 
			L"Title: "  + handle.GetWindowTitle() + L"\n"
			L"Class: "  + handle.GetWindowTitle() + L"\n"
			L"Handle: " + std::wstring(handle)    + L"\n";
	}
};


export class NativeWindowBackground final : public INativeBackgroundInfo
{
private:
	const NativeWindowHandle handle;

public:
	NativeWindowBackground(NativeWindowHandle const& handle) : handle(handle) { }

	NativeWindowHandle GetHandle() { return handle; }
};


export class NativeApplicationBackground : public INativeBackgroundInfo
{
private:
	const std::wstring commandline;
	const std::wstring currentDir;

	PROCESS_INFORMATION pInfo;
	std::vector<HWND> hWnds;

public:
	NativeApplicationBackground(std::wstring const& commandline, std::wstring const& exeDir)
		: commandline(commandline), currentDir(exeDir) { }

	NativeWindowHandle GetWindowHandle() {
		// TODO: 有缺陷, 如果没有句柄或不是用户想要的句柄咋办
		return NativeWindowHandle(*hWnds.begin());
	}

	bool IsProcessAvailable() {
		DWORD code;
		return GetExitCodeProcess(pInfo.hProcess, &code) &&
			code == STILL_ACTIVE;
	}

	bool IsAvailable() { return IsProcessAvailable() && INativeBackgroundInfo::IsAvailable(); }

	bool Launch() {
		if (IsProcessAvailable()) return true;

		STARTUPINFO sInfo;

		ZeroMemory(&sInfo, sizeof(sInfo));
		ZeroMemory(&pInfo, sizeof(pInfo));
		sInfo.cb = sizeof(sInfo);
		
		if (!CreateProcess(nullptr, const_cast<LPWSTR>(commandline.c_str()),
						   nullptr, nullptr, false, 0, nullptr, currentDir.c_str(),
						   &sInfo, &pInfo))
			return false;
		
		hWnds = GetHWNDsFromPID(pInfo.dwProcessId);
		return true;
	}
};
