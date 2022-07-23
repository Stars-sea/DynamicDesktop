#pragma once

#include "MainWindow.g.h"

using namespace winrt::Microsoft::UI;
using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        // https://docs.microsoft.com/zh-cn/windows/apps/windows-app-sdk/system-backdrop-controller
        Windows::System::DispatcherQueueController                         dqController = nullptr;
        Composition::SystemBackdrops::SystemBackdropConfiguration          bdConfig     = nullptr;
        Composition::SystemBackdrops::ISystemBackdropControllerWithTargets bdController = nullptr;
        
        Window::Activated_revoker                    activatedRevoker;
        Window::Closed_revoker                       closedRevoker;
        FrameworkElement::ActualThemeChanged_revoker themeChangedRevoker;

        MainWindow();

        bool SetBackdrop();
        void SetupBackdropConfig();
    };
}

namespace winrt::DynamicDesktop::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
