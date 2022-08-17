#include "pch.h"
#include "Core.WindowHandleWrapper.h"
#if __has_include("Core.WindowHandleWrapper.g.cpp")
#include "Core.WindowHandleWrapper.g.cpp"
#endif

namespace winrt::DynamicDesktop::Core::implementation
{
	WindowHandleWrapper::WindowHandleWrapper(const size_t& hId) : 
		handle(WindowHandle(hId)) { }
	WindowHandleWrapper::WindowHandleWrapper(const hstring& name, bool isTitle) :
	    handle(WindowHandle(name.c_str(), isTitle)) { }

	bool WindowHandleWrapper::Cover()   const { return handle.Cover(); }
	void WindowHandleWrapper::Uncover() const { handle.Uncover(); }

	bool WindowHandleWrapper::Valid() const { return handle.Valid(); }

	hstring WindowHandleWrapper::ToString() const { return std::wstring(handle).c_str(); }

	bool WindowHandleWrapper::Equals(const IInspectable& other) const
	{
		auto wrapper = other.try_as<Core::WindowHandleWrapper>();
		return wrapper != nullptr && HId() == wrapper.HId();
	}
}
