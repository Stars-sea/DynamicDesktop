#pragma once

#include "Core.ApplicationBackground.g.h"

#include <memory>
#include <vector>
#include <string>
#include <Windows.h>

namespace winrt::DynamicDesktop::Core::implementation
{
    struct ApplicationBackground : ApplicationBackgroundT<ApplicationBackground, WindowBackground>
    {
    public:
        Core::WindowHandle Handle();

        Windows::Foundation::Collections::IVectorView<Core::WindowHandle> Handles() const { return handles.GetView(); }

        bool IsProcessAvailable();
        bool IsAvailable();

        ApplicationBackground(hstring commandline, hstring workingDir) 
            : commandline(commandline), workingDir(workingDir) { }

        bool Launch();

    private:
        const hstring commandline;
        const hstring workingDir;

        std::shared_ptr<PROCESS_INFORMATION> pInfo{ nullptr };
        Windows::Foundation::Collections::IVector<Core::WindowHandle> handles;
    };
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
    struct ApplicationBackground : ApplicationBackgroundT<ApplicationBackground, implementation::ApplicationBackground>
    {
    };
}
