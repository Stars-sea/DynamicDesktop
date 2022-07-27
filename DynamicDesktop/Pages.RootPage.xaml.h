#pragma once

#include "Pages.RootPage.g.h"

using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct RootPage : RootPageT<RootPage>
    {
        RootPage();

        void NavigationItemSelected(
            NavigationView const& sender, 
            NavigationViewSelectionChangedEventArgs const& args
        );
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct RootPage : RootPageT<RootPage, implementation::RootPage>
    {
    };
}
