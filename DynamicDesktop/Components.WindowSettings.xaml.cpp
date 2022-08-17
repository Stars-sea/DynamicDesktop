#include "pch.h"
#include "Components.WindowSettings.xaml.h"
#if __has_include("Components.WindowSettings.g.cpp")
#include "Components.WindowSettings.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace Windows::UI::Xaml::Interop;

namespace winrt::DynamicDesktop::Components::implementation
{
    const DependencyProperty WindowSettings::innerHandleProperty = DependencyProperty::Register(
        L"InnerHandle",
        xaml_typename<DynamicDesktop::Core::WindowHandleWrapper>(),
        xaml_typename<DynamicDesktop::Components::WindowSettings>(),
        PropertyMetadata{ nullptr }
    );

    WindowSettings::WindowSettings()
    {
        InitializeComponent();
    }
}
