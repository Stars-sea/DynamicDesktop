#pragma once

#include "Core.WindowBackground.g.h"

#include "Core.WindowHandle.h"

namespace winrt::DynamicDesktop::Core::implementation
{
    struct WindowBackground : WindowBackgroundT<WindowBackground>
    {
    private:
        Core::WindowHandle handle;

    public:
        Core::WindowHandle Handle() { return handle; }
        bool IsAvailable() { return handle.Valid(); }

        bool IsEnabled() const { return handle.IsEnabled(); }
        void IsEnabled(bool value) { handle.IsEnabled(value); }

        Windows::Foundation::Collections::IObservableMap<hstring, hstring> Details();

        WindowBackground(Core::WindowHandle handle) : handle(handle) { }
    };
}
namespace winrt::DynamicDesktop::Core::factory_implementation
{
    struct WindowBackground : WindowBackgroundT<WindowBackground, implementation::WindowBackground>
    {
    };
}