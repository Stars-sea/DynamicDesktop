#include "pch.h"
#include "Pages.RootPage.xaml.h"
#if __has_include("Pages.RootPage.g.cpp")
#include "Pages.RootPage.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Interop.h>

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
        // TODO: 导航会导致 HomePage 数据丢失
        using Frame = Controls::Frame;
        using namespace Windows::UI::Xaml::Interop;

        NavigationViewItem item = args.SelectedItem().try_as<NavigationViewItem>();
        if (item != nullptr) {
            hstring type  = item.Tag().as<hstring>();
            Frame   frame = contentFrame();
            if (type == L"HomePage")
                frame.SourcePageType(xaml_typename<HomePage>());
            else if (type == L"AboutPage")
                frame.SourcePageType(xaml_typename<AboutPage>());
        }
    }
}
