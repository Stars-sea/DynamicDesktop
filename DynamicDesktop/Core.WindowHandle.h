#pragma once

#include "Core.WindowHandle.g.h"

#include <map>

import DynamicDesktop.Core.Handle;

namespace winrt::DynamicDesktop::Core::implementation
{
	struct WindowHandle : WindowHandleT<WindowHandle>
	{
	public:
		static Core::WindowHandle Empty() { return empty; }

		size_t  HId()         const { return handle.hId; }
		hstring HexId()       const { return ToString(); }
		bool    IsCovered()   const { return handle.IsCovered(); }
		hstring WindowTitle() const { return hstring(handle.GetWindowTitle().c_str()); }
		hstring WindowClass() const { return hstring(handle.GetWindowClass().c_str()); }
		size_t  WindowIcon()  const { return (size_t)handle.GetWindowIcon();  }

		bool IsEnabled() const;
		void IsEnabled(bool value);

		Windows::Foundation::Collections::IObservableMap<hstring, hstring> Details() {			
			std::map<hstring, hstring> m;
			for (auto pair : handle.GetDetails()) {
				m[pair.first.c_str()] = pair.second.c_str();
			}
			return multi_threaded_observable_map<hstring, hstring>(std::move(m));
		}

		WindowHandle(const NativeWindowHandle& handle) : handle(handle) { }
		WindowHandle(const size_t& hId);
		WindowHandle(const hstring& name, bool isTitle);
		
		bool Valid() const;

		hstring ToString() const;
		bool Equals(const IInspectable& other) const;
	private:
		static const Core::WindowHandle empty;

		const NativeWindowHandle handle;
	};
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
	struct WindowHandle : WindowHandleT<WindowHandle, implementation::WindowHandle>
	{
	};
}
