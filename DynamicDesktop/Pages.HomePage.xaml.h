#pragma once

#include "Pages.HomePage.g.h"
#include "Core.WindowHandleWrapper.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;

using Handle = DynamicDesktop::Core::WindowHandleWrapper;

namespace winrt::DynamicDesktop::Pages::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        Collections::IObservableVector<Handle> Wrappers() { return wrappers; }
        Handle SelectedHandle() const { return selectedHandle; }

        HomePage();

        void OnPaneOpening(Controls::SplitView const& sender, IInspectable const& args);
        void OnPaneClosing(Controls::SplitView const& sender, Controls::SplitViewPaneClosingEventArgs const& args);
        void OnSelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& args);
        void OnLoaded(IInspectable const& sender, RoutedEventArgs const& args);
        void OnAddHandleClick(IInspectable const& sender, RoutedEventArgs const& args);
    private:
        Collections::IObservableVector<Handle> wrappers = multi_threaded_observable_vector<Handle>();
        Handle selectedHandle = nullptr;
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
