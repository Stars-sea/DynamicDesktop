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
        static DependencyProperty SelectedHandleProperty() { return selectedHandleProperty; }

        Collections::IObservableVector<Handle> Handles() { return handles; }

        Handle SelectedHandle() const {
            return unbox_value<Handle>(GetValue(selectedHandleProperty));
        }
        void SelectedHandle(Handle const& value) {
            SetValue(selectedHandleProperty, box_value(value));
        }

        HomePage();

        bool AppendHandle(const Handle& handle);
        bool RemoveHandle(const Handle& handle);

        void OnPaneOpening(Controls::SplitView const&, IInspectable const&);
        fire_and_forget OnPaneClosing(Controls::SplitView const&, Controls::SplitViewPaneClosingEventArgs const&);
        void OnDeleteHandleClick(IInspectable const&, RoutedEventArgs const&);
        void OnItemClick(IInspectable const&, Controls::ItemClickEventArgs const&);
        void OnAddHandleClick(IInspectable const&, RoutedEventArgs const&);
    private:
        static const DependencyProperty selectedHandleProperty;
        static const DependencyProperty hasSelectedHandleProperty;

        Collections::IObservableVector<Handle> handles = multi_threaded_observable_vector<Handle>();

        fire_and_forget ShowTempMessage(const Controls::InfoBar& info);
    };
}

namespace winrt::DynamicDesktop::Pages::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
