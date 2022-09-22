#include "pch.h"
#include "Core.ApplicationBackground.h"
#if __has_include("Core.ApplicationBackground.g.cpp")
#include "Core.ApplicationBackground.g.cpp"
#endif

import DynamicDesktop.Core.HandleHelper;
using namespace winrt::Windows::Foundation;

namespace winrt::DynamicDesktop::Core::implementation
{
	Core::WindowHandle ApplicationBackground::Handle()
	{
		// TODO: 有缺陷, 如果没有句柄或不是用户想要的句柄咋办
		return (handles.Size() == 0)
			? Core::WindowHandle::Empty()
			: handles.GetAt(0);
	}

	bool ApplicationBackground::IsProcessAvailable()
	{
		if (pInfo.get() == nullptr) return false;

		DWORD code;
		return GetExitCodeProcess(pInfo->hProcess, &code) &&
			code == STILL_ACTIVE;
	}

	bool ApplicationBackground::IsAvailable()
	{
		return IsProcessAvailable() && impl::producer_ref<Core::WindowBackground>(this).IsAvailable();
	}

	bool ApplicationBackground::Launch()
	{
		if (IsProcessAvailable()) return true;

		STARTUPINFO sInfo;
		pInfo = std::shared_ptr<PROCESS_INFORMATION>{};

		ZeroMemory(&sInfo, sizeof(sInfo));
		ZeroMemory(pInfo.get(), sizeof(pInfo));
		sInfo.cb = sizeof(sInfo);

		if (!CreateProcess(nullptr, const_cast<LPWSTR>(commandline.c_str()),
						   nullptr, nullptr, false, 0, nullptr, workingDir.c_str(),
						   &sInfo, pInfo.get()))
			return false;

		auto hWnds = GetHWNDsFromPID(pInfo->dwProcessId);
		std::vector<Core::WindowHandle> v;
		for (HWND hWnd : hWnds)
			v.push_back(Core::WindowHandle((uint64_t)hWnd));
		handles = single_threaded_vector<Core::WindowHandle>(std::move(v));

		return true;
	}
}
