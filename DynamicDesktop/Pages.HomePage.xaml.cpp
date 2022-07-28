#include "pch.h"
#include "Pages.HomePage.xaml.h"
#if __has_include("Pages.HomePage.g.cpp")
#include "Pages.HomePage.g.cpp"
#endif

#include "App.xaml.h"

namespace winrt::DynamicDesktop::Pages::implementation
{
    auto GetPaneAnime(float finalValue)
    {
        using DynamicDesktop::implementation::App;

        App* app = Microsoft::UI::Xaml::Application::Current().as<App>().get();
        auto anime = app->CurrentWindow().Compositor().CreateSpringScalarAnimation();

        anime.Target(L"Opacity");
        anime.FinalValue(IReference(finalValue));
        anime.Period(TimeSpan(1000));

        return anime;
    }

    HomePage::HomePage() : paneOpenAnime(GetPaneAnime(1)), paneCloseAnime(GetPaneAnime(0))
    {
        InitializeComponent();
    }

    void HomePage::OnPaneOpening(Controls::SplitView const&, IInspectable const&)
    {
        AcrylicMask().Visibility(Visibility::Visible);
        AcrylicMask().StartAnimation(paneOpenAnime);
    }

    void HomePage::OnPaneClosing(Controls::SplitView const&, Controls::SplitViewPaneClosingEventArgs const&)
    {
        AcrylicMask().StartAnimation(paneCloseAnime);
        AcrylicMask().Visibility(Visibility::Collapsed);
    }

    void HomePage::OnSelectionChanged(IInspectable const&, Controls::SelectionChangedEventArgs const&)
    {
    }

    void HomePage::OnLoaded(IInspectable const&, RoutedEventArgs const&)
    {

    }
    void HomePage::OnTestClick(IInspectable const& sender, RoutedEventArgs const& args)
    {
        Root().IsPaneOpen(!Root().IsPaneOpen());
    }
}
