#pragma once

#include "Core.WindowHandleWrapper.g.h"

import DynamicDesktop.Core;

namespace winrt::DynamicDesktop::Core::implementation
{
	struct WindowHandleWrapper : WindowHandleWrapperT<WindowHandleWrapper>
	{
	public:
		size_t HId() { return hId; }

		WindowHandleWrapper(size_t hId);

		bool Cover();
		void Uncover();

		bool Valid();
		bool IsCovered();

		winrt::hstring ToString();
	private:
		const size_t hId;
		const WindowHandle handle;
	};
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
	struct WindowHandleWrapper : WindowHandleWrapperT<WindowHandleWrapper, implementation::WindowHandleWrapper>
	{
	};
}
