#pragma once

#include "Core.ApplicationBackground.g.h"

#include <vector>
#include <string>
#include <Windows.h>

namespace winrt::DynamicDesktop::Core::implementation
{
    struct ApplicationBackground : ApplicationBackgroundT<ApplicationBackground, WindowBackground>, private WindowBackground
    {
    public:
        // TODO: 完善 ApplicationBackground

        bool IsProcessAvailable();

        ApplicationBackground(hstring commandline, hstring workingDir) 
            : commandline(commandline), workingDir(workingDir), WindowBackground() { }

        bool Launch();

    private:
        const hstring commandline;
        const hstring workingDir;

        PROCESS_INFORMATION pInfo;
        std::vector<HWND> hWnds;
    };
}

namespace winrt::DynamicDesktop::Core::factory_implementation
{
    struct ApplicationBackground : ApplicationBackgroundT<ApplicationBackground, implementation::ApplicationBackground>
    {
    };
}
