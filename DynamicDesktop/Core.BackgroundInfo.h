#pragma once

#include <map>

#include "Core.IBackgroundInfo.g.h"
#include "Core.WindowBackground.g.h"
#include "Core.WindowHandle.h"

import DynamicDesktop.Core.BackgroundInfo;

using namespace winrt::Windows::Foundation;

namespace winrt::DynamicDesktop::Core::implementation {
	struct IBackgroundInfo : IBackgroundInfoT<IBackgroundInfo>
	{
	public:
		virtual Core::WindowHandle Handle() = 0;
		virtual bool IsAvailable() { return Handle().Valid(); }
		virtual Collections::IObservableMap<hstring, hstring> Details();
	};

	struct WindowBackground : WindowBackgroundT<WindowBackground, IBackgroundInfo>
	{
	private:
		const Core::WindowHandle handle;

	public:
		Core::WindowHandle Handle() { return handle; }

		WindowBackground(WindowHandle const& handle) : handle(handle) { }

	};
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
	struct WindowBackground : WindowBackgroundT<WindowBackground, implementation::WindowHandle>
	{
	};
}
