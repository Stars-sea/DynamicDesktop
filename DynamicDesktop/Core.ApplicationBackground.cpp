#include "pch.h"
#include "Core.ApplicationBackground.h"
#if __has_include("Core.ApplicationBackground.g.cpp")
#include "Core.ApplicationBackground.g.cpp"
#endif

import DynamicDesktop.Core.HandleHelper;

namespace winrt::DynamicDesktop::Core::implementation
{
	bool ApplicationBackground::IsProcessAvailable()
	{
		DWORD code;
		return GetExitCodeProcess(pInfo.hProcess, &code) &&
			code == STILL_ACTIVE;
	}

	bool ApplicationBackground::Launch()
	{
		if (IsProcessAvailable()) return true;

		STARTUPINFO sInfo;

		ZeroMemory(&sInfo, sizeof(sInfo));
		ZeroMemory(&pInfo, sizeof(pInfo));
		sInfo.cb = sizeof(sInfo);

		if (!CreateProcess(nullptr, const_cast<LPWSTR>(commandline.c_str()),
						   nullptr, nullptr, false, 0, nullptr, workingDir.c_str(),
						   &sInfo, &pInfo))
			return false;

		hWnds = GetHWNDsFromPID(pInfo.dwProcessId);
		return true;
	}
}
