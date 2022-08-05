#include "pch.h"
#include "Pages.HomePage.xaml.h"
#if __has_include("Pages.HomePage.g.cpp")
#include "Pages.HomePage.g.cpp"
#endif

namespace winrt::DynamicDesktop::Pages::implementation
{
    const DependencyProperty HomePage::selectedHandleProperty = DependencyProperty::Register(
        L"SelectedHandle",
        xaml_typename<DynamicDesktop::Core::WindowHandleWrapper>(),
        xaml_typename<DynamicDesktop::Pages::HomePage>(),
        PropertyMetadata(nullptr)
    );

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

    void HomePage::OnSelectionChanged(IInspectable const&, Controls::SelectionChangedEventArgs const&)
    {
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
