#pragma once

#include "Pages.AboutPage.g.h"

using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct AboutPage : AboutPageT<AboutPage>
    {
        AboutPage();

        void OnLoaded(Windows::Foundation::IInspectable const&, RoutedEventArgs const&);
        void OnRepoClick(Windows::Foundation::IInspectable const&, RoutedEventArgs const&);
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}
