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

    void HomePage::OnPaneOpening(Controls::SplitView const&, IInspectable const&)
    {
        AcrylicMask().Visibility(Visibility::Visible);
        AcrylicMask().Opacity(1);
    }

    void HomePage::OnPaneClosing(Controls::SplitView const&, Controls::SplitViewPaneClosingEventArgs const&)
    {
        AcrylicMask().Opacity(0);
        AcrylicMask().Visibility(Visibility::Collapsed);
    }

    void HomePage::OnSelectionChanged(IInspectable const&, Controls::SelectionChangedEventArgs const& args)
    {
        selectedHandle = (*args.AddedItems().First()).as<Handle>();
        Root().IsPaneOpen(true);
    }

    void HomePage::OnLoaded(IInspectable const&, RoutedEventArgs const&)
    {
    }

    void HomePage::OnAddHandleClick(IInspectable const&, RoutedEventArgs const&)
    {
        // Test
        Handle wrapper(L"WinUI 3 Gallery", true);
        Wrappers().Append(wrapper);
    }
}
