#include "pch.h"
#include "Pages.HomePage.xaml.h"
#if __has_include("Pages.HomePage.g.cpp")
#include "Pages.HomePage.g.cpp"
#endif

#include "Components.WindowSettings.xaml.h"

namespace winrt::DynamicDesktop::Pages::implementation
{
    const DependencyProperty HomePage::selectedHandleProperty = DependencyProperty::Register(
        L"SelectedHandle",
        xaml_typename<Handle>(),
        xaml_typename<Pages::HomePage>(),
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

        for (UIElement&& e : SideBar().Children()) {
            e.Visibility(Visibility::Collapsed);
        }
    }

    void HomePage::OnDeleteHandleClick(IInspectable const& sender, RoutedEventArgs const&)
    {
        Handle handle  = sender.as<Controls::Button>().Tag().as<Handle>();
        auto   handles = Wrappers();
        for (uint32_t i = 0; i < handles.Size(); i++) {
            if (handle == handles.GetAt(i)) {
                handles.RemoveAt(i);
                break;
            }
        }
    }

    void HomePage::OnItemClick(IInspectable const&, Controls::ItemClickEventArgs const&)
    {
        for (UIElement&& e : SideBar().Children()) {
            if (e.try_as<Components::WindowSettings>() != nullptr) {
                e.Visibility(Visibility::Visible);
                break;
            }
        }
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
