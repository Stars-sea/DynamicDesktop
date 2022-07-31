#include "pch.h"
#include "Core.WindowHandleWrapper.h"
#if __has_include("Core.WindowHandleWrapper.g.cpp")
#include "Core.WindowHandleWrapper.g.cpp"
#endif

namespace winrt::DynamicDesktop::Core::implementation
{
	WindowHandleWrapper::WindowHandleWrapper(const size_t& hId) : 
		handle(WindowHandle(hId)) { }
	WindowHandleWrapper::WindowHandleWrapper(const hstring& className, const hstring& windowName) :
	    handle(WindowHandle(className.c_str(), windowName.c_str())) { }

	bool WindowHandleWrapper::Cover() { return handle.Cover(); }
	void WindowHandleWrapper::Uncover() { handle.Uncover(); }

	bool WindowHandleWrapper::Valid() { return handle.Valid(); }
	bool WindowHandleWrapper::IsCovered() { return handle.IsCovered(); }

	winrt::hstring WindowHandleWrapper::ToString() { return std::wstring(handle).c_str(); }
}
