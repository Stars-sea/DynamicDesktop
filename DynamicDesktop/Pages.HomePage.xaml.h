#pragma once

#include "Pages.HomePage.g.h"
#include "Core.WindowHandleWrapper.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        Collections::IObservableVector<Core::WindowHandleWrapper> Wrappers() { return wrappers; }

        void OnPaneOpening(Controls::SplitView const& sender, IInspectable const& args);
        void OnPaneClosing(Controls::SplitView const& sender, Controls::SplitViewPaneClosingEventArgs const& args);
        void OnSelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& args);
        void OnLoaded(IInspectable const& sender, RoutedEventArgs const& args);
        void OnTestClick(IInspectable const& sender, RoutedEventArgs const& args);
    private:
        Collections::IObservableVector<Core::WindowHandleWrapper> wrappers;
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
