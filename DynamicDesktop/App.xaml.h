#pragma once

#include "App.xaml.g.h"

namespace winrt::DynamicDesktop::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

        Microsoft::UI::Xaml::Window CurrentWindow() { return window; }
    private:
        Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
