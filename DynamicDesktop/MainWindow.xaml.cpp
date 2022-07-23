#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Windows::System;
using namespace Microsoft::UI::Composition::SystemBackdrops;

namespace winrt::DynamicDesktop::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        // TitleBar Settings
        Title(Windows::ApplicationModel::AppInfo::Current().DisplayInfo().DisplayName());
        ExtendsContentIntoTitleBar(true);
        SetTitleBar(TitleBar());

        // Backdrop Settings
        SetBackdrop();
        closedRevoker = this->Closed(winrt::auto_revoke,
            [&](auto&&, auto&&) {
                if (bdController != nullptr) {
                    bdController.Close();
                    bdController = nullptr;
                }
                if (dqController != nullptr) {
                    dqController.ShutdownQueueAsync();
                    dqController = nullptr;
                }
            });
    }

    bool MainWindow::SetBackdrop()
    {
        if (MicaController::IsSupported())
            bdController = MicaController();
        else if (DesktopAcrylicController::IsSupported())
            bdController = DesktopAcrylicController();

        if (bdController != nullptr) {
            // Init DispatcherQueueController
            if (DispatcherQueue::GetForCurrentThread() == nullptr && dqController == nullptr) {
                DispatcherQueueOptions options
                {
                    sizeof(DispatcherQueueOptions),
                    DQTYPE_THREAD_CURRENT,
                    DQTAT_COM_NONE
                };

                ::ABI::Windows::System::IDispatcherQueueController* ptr{ nullptr };
                winrt::check_hresult(CreateDispatcherQueueController(options, &ptr));
                dqController = { ptr, take_ownership_from_abi };
            }

            SetupBackdropConfig();
            bdController.SetSystemBackdropConfiguration(bdConfig);
            bdController.AddSystemBackdropTarget(this->try_as<Composition::ICompositionSupportsSystemBackdrop>());
            return true;
        }
        return false;
    }

    void MainWindow::SetupBackdropConfig()
    {
        bdConfig = SystemBackdropConfiguration();
        activatedRevoker = this->Activated(winrt::auto_revoke,
            [&](auto&&, WindowActivatedEventArgs const& args) {
                bdConfig.IsInputActive(WindowActivationState::Deactivated != args.WindowActivationState());
            });

        bdConfig.IsInputActive(true);
        auto rootElement = Content().try_as<FrameworkElement>();
        if (rootElement != nullptr) {
            themeChangedRevoker = rootElement.ActualThemeChanged(winrt::auto_revoke,
                [&](FrameworkElement e, auto&&) {
                    int32_t enumNum = static_cast<int32_t>(e.ActualTheme());
                    bdConfig.Theme(SystemBackdropTheme(enumNum));
                });
            int32_t enumNum = static_cast<int32_t>(rootElement.ActualTheme());
            bdConfig.Theme(SystemBackdropTheme(enumNum));
        }
    }
}
