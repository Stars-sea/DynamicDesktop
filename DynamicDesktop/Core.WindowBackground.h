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
        virtual bool IsAvailable() { return handle.Valid(); }

        Windows::Foundation::Collections::IObservableMap<hstring, hstring> Details();

        WindowBackground(Core::WindowHandle handle) : handle(handle) { }

    protected:
        WindowBackground() = default;
        // void SetHandle(Core::WindowHandle const& handle) { this->handle = handle; }
    };
}
namespace winrt::DynamicDesktop::Core::factory_implementation
{
    struct WindowBackground : WindowBackgroundT<WindowBackground, implementation::WindowBackground>
    {
    };
}