#include "pch.h"
#include "Core.WindowHandle.h"
#if __has_include("Core.WindowHandle.g.cpp")
#include "Core.WindowHandle.g.cpp"
#endif

namespace winrt::DynamicDesktop::Core::implementation
{
	const Core::WindowHandle WindowHandle::empty = Core::WindowHandle(static_cast<uint64_t>(0));

	bool WindowHandle::IsEnabled() const { return handle.IsCovered(); }

	void WindowHandle::IsEnabled(bool value)
	{
		if (value) handle.Cover();
		else handle.Uncover();
	}

	WindowHandle::WindowHandle(const size_t& hId) :
		handle(NativeWindowHandle(hId)) { }
	WindowHandle::WindowHandle(const hstring& name, bool isTitle) :
	    handle(NativeWindowHandle(name.c_str(), isTitle)) { }

	bool WindowHandle::Valid() const { return handle.Valid(); }

	hstring WindowHandle::ToString() const { return std::wstring(handle).c_str(); }

	bool WindowHandle::Equals(const IInspectable& other) const
	{
		auto wrapper = other.try_as<Core::WindowHandle>();
		return wrapper != nullptr && HId() == wrapper.HId();
	}
}
