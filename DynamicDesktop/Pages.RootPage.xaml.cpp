#include "pch.h"
#include "Pages.RootPage.xaml.h"
#if __has_include("Pages.RootPage.g.cpp")
#include "Pages.RootPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::Pages::implementation
{
    RootPage::RootPage()
    {
        InitializeComponent();
    }

    void RootPage::NavigationItemSelected(
        NavigationView const&, 
        NavigationViewSelectionChangedEventArgs const& args
    ) {
        NavigationViewItem item = args.SelectedItem().try_as<NavigationViewItem>();
        if (item != nullptr) {
            Page page = item.Tag().as<Page>();
            contentFrame().Content(page);
        }
    }
}
