#include "pch.h"
#include "Pages.AboutPage.xaml.h"
#if __has_include("Pages.AboutPage.g.cpp")
#include "Pages.AboutPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::Pages::implementation
{
    AboutPage::AboutPage()
    {
        InitializeComponent();
    }

    int32_t AboutPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AboutPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AboutPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
