#include "pch.h"
#include "Pages.AboutPage.xaml.h"
#if __has_include("Pages.AboutPage.g.cpp")
#include "Pages.AboutPage.g.cpp"
#endif

using namespace winrt;

namespace winrt::DynamicDesktop::Pages::implementation
{
    AboutPage::AboutPage()
    {
        InitializeComponent();
    }

    void AboutPage::OnLoaded(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        auto version = Windows::ApplicationModel::Package::Current().Id().Version();
        DisplayVersion().Text(
            std::format(L"v{}.{}.{}.{}", 
                version.Major, 
                version.Minor, 
                version.Build, 
                version.Revision
            ));
    }

    void AboutPage::OnRepoClick(Windows::Foundation::IInspectable const&, RoutedEventArgs const&)
    {
        ShellExecute(NULL, L"open", L"https://github.com/Stars-sea/DynamicDesktop", NULL, NULL, NULL);
    }
}
