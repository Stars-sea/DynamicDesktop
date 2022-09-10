#include "pch.h"
#include "Core.BackgroundInfo.h"

#if __has_include("Core.IBackgroundInfo.g.h")
#include "Core.IBackgroundInfo.g.h"
#endif

namespace winrt::DynamicDesktop::Core::implementation
{
	Collections::IObservableMap<hstring, hstring> IBackgroundInfo::Details() {
		Core::WindowHandle handle = Handle();

		std::map<hstring, hstring> m;
		m[L"Title"]  = handle.WindowTitle();
		m[L"Class"]  = handle.WindowClass();
		m[L"Handle"] = handle.ToString();
		return multi_threaded_observable_map(std::move(m));
	}


}
