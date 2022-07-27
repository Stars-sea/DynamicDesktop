#pragma once

#include "Pages.HomePage.g.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        void OnSelectionChanged(Windows::Foundation::IInspectable const& sender, Controls::SelectionChangedEventArgs const& args);
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
