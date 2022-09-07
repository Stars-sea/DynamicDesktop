#include "pch.h"
#include "Pages.HomePage.xaml.h"
#if __has_include("Pages.HomePage.g.cpp")
#include "Pages.HomePage.g.cpp"
#endif

#include <chrono>

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

    bool HomePage::AppendHandle(const Handle& handle)
    {
        if (handle == nullptr || !handle.Valid()) {
            Controls::InfoBar info;
            info.Message(L"加入无效句柄");
            info.Severity(Controls::InfoBarSeverity::Warning);
            ShowTempMessage(info);
            
            return false;
        }
        
        for (Handle&& current : handles) {
            if (handle.Equals(current)) {
                Controls::InfoBar info;
                info.Message(L"已存在相同句柄");
                info.Severity(Controls::InfoBarSeverity::Warning);
                ShowTempMessage(info);

                SelectedHandle(current);

                return false;
            }
        }
        handles.Append(handle);
        return true;
    }

    bool HomePage::RemoveHandle(const Handle& handle)
    {
        if (handle == nullptr) return false;

        for (uint32_t i = 0; i < handles.Size(); i++) {
            if (handle == handles.GetAt(i)) {
                handles.RemoveAt(i);
                return true;
            }
        }
        return false;
    }

    void HomePage::OnPaneOpening(Controls::SplitView const&, IInspectable const&)
    {
        AcrylicMask().Visibility(Visibility::Visible);
        AcrylicMask().Opacity(1);
    }

    fire_and_forget HomePage::OnPaneClosing(Controls::SplitView const&, Controls::SplitViewPaneClosingEventArgs const&)
    {
        using namespace std::chrono_literals;

        apartment_context context;
        AcrylicMask().Opacity(0);

        co_await resume_after(300ms);
        co_await context;

        AcrylicMask().Visibility(Visibility::Collapsed);

        for (UIElement&& e : SideBar().Children()) {
            e.Visibility(Visibility::Collapsed);
        }
    }

    void HomePage::OnDeleteHandleClick(IInspectable const& sender, RoutedEventArgs const&)
    {
        auto button = sender.as<Controls::Button>();
        RemoveHandle(button.Tag().as<Handle>());
    }

    void HomePage::OnItemClick(IInspectable const&, Controls::ItemClickEventArgs const& args)
    {
        if (SelectedHandle() != args.ClickedItem())
            return;

        // TODO: 找到直接打开的方法, XAML 给自定义元素命名会报错
        for (UIElement&& e : SideBar().Children()) {
            if (e.try_as<Components::WindowSettings>() != nullptr) {
                e.Visibility(Visibility::Visible);
                break;
            }
        }
        Root().IsPaneOpen(true);
    }

    void HomePage::OnAddHandleClick(IInspectable const&, RoutedEventArgs const&)
    {
        // Test
        Handle handle(L"WinUI 3 Gallery", true);
        AppendHandle(handle);
    }

    fire_and_forget HomePage::ShowTempMessage(const Controls::InfoBar& info)
    {
        using namespace std::chrono_literals;

        Controls::UIElementCollection collection = InfoContainer().Children();

        collection.Append(info);
        info.IsOpen(true);

        apartment_context context;
        co_await resume_after(2s);
        co_await context;

        // TODO: 此方法会报错, 只好无脑写...
        /*
        for (uint32_t i = 0; i < collection.Size(); i++) {
            if (info == collection.GetAt(i)) {
                collection.RemoveAt(i);
                break;
            }
        } */
        collection.RemoveAtEnd();
    }
}
