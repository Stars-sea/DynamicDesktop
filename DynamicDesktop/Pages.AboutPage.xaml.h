#pragma once

#include "Pages.AboutPage.g.h"

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct AboutPage : AboutPageT<AboutPage>
    {
        AboutPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}
