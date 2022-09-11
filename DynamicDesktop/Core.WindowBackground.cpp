#include "pch.h"
#include "Core.WindowBackground.h"
#if __has_include("Core.WindowBackground.g.cpp")
#include "Core.WindowBackground.g.cpp"
#endif

#include <map>

using namespace winrt::Windows::Foundation;

namespace winrt::DynamicDesktop::Core::implementation
{
	Collections::IObservableMap<hstring, hstring> WindowBackground::Details()
	{
		std::map<hstring, hstring> m;
		m[L"Title"]  = handle.WindowTitle();
		m[L"Class"]  = handle.WindowClass();
		m[L"Handle"] = handle.ToString();		
		
		return multi_threaded_observable_map<hstring, hstring>(std::move(m));
	}
}
