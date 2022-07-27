#include "pch.h"
#include "Pages.HomePage.xaml.h"
#if __has_include("Pages.HomePage.g.cpp")
#include "Pages.HomePage.g.cpp"
#endif

namespace winrt::DynamicDesktop::Pages::implementation
{
    HomePage::HomePage()
    {
        InitializeComponent();
    }

    void HomePage::OnSelectionChanged(Windows::Foundation::IInspectable const& sender, Controls::SelectionChangedEventArgs const& args)
    {
    }
}
