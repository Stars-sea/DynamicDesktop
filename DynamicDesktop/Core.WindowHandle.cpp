#include "pch.h"
#include "Core.WindowHandle.h"
#if __has_include("Core.WindowHandle.g.cpp")
#include "Core.WindowHandle.g.cpp"
#endif

namespace winrt::DynamicDesktop::Core::implementation
{
	WindowHandle::WindowHandle(const size_t& hId) : 
		handle(NativeWindowHandle(hId)) { }
	WindowHandle::WindowHandle(const hstring& name, bool isTitle) :
	    handle(NativeWindowHandle(name.c_str(), isTitle)) { }

	bool WindowHandle::Cover()   const { return handle.Cover(); }
	void WindowHandle::Uncover() const { handle.Uncover(); }

	bool WindowHandle::Valid() const { return handle.Valid(); }

	hstring WindowHandle::ToString() const { return std::wstring(handle).c_str(); }

	bool WindowHandle::Equals(const IInspectable& other) const
	{
		auto wrapper = other.try_as<Core::WindowHandle>();
		return wrapper != nullptr && HId() == wrapper.HId();
	}
}
