#pragma once

#include "Components.WindowSettings.g.h"
#include "Core.WindowHandleWrapper.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

using Handle = DynamicDesktop::Core::WindowHandleWrapper;

namespace winrt::DynamicDesktop::Components::implementation
{
    struct WindowSettings : WindowSettingsT<WindowSettings>
    {
        static DependencyProperty InnerHandleProperty() { return innerHandleProperty; }

        Handle InnerHandle() const { return unbox_value<Handle>(GetValue(innerHandleProperty));  }
        void InnerHandle(Handle const& value) { SetValue(innerHandleProperty, box_value(value)); }

        WindowSettings();

    private:
        static const DependencyProperty innerHandleProperty;
    };
}

namespace winrt::DynamicDesktop::Components::factory_implementation
{
    struct WindowSettings : WindowSettingsT<WindowSettings, implementation::WindowSettings>
    {
    };
}
