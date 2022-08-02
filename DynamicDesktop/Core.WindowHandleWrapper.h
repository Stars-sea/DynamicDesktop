#pragma once

#include "Core.WindowHandleWrapper.g.h"

import DynamicDesktop.Core;

namespace winrt::DynamicDesktop::Core::implementation
{
	struct WindowHandleWrapper : WindowHandleWrapperT<WindowHandleWrapper>
	{
	public:
		size_t  HId()         const { return handle.hId; }
		hstring HexId()       const { return L"0x" + ToString(); }
		bool    IsCovered()   const { return handle.IsCovered(); }
		hstring WindowTitle() const { return hstring(handle.GetWindowTitle().c_str()); }
		hstring WindowClass() const { return hstring(handle.GetWindowClass().c_str()); }
		size_t  WindowIcon()  const { return (size_t)handle.GetWindowIcon();  }

		WindowHandleWrapper(const size_t& hId);
		WindowHandleWrapper(const hstring& name, bool isTitle);

		bool Cover() const;
		void Uncover() const;

		bool Valid() const;

		hstring ToString() const;
	private:
		const WindowHandle handle;
	};
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
	struct WindowHandleWrapper : WindowHandleWrapperT<WindowHandleWrapper, implementation::WindowHandleWrapper>
	{
	};
}
