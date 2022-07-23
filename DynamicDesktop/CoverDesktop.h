#pragma once

#include "pch.h"
#include <list>

namespace DynamicDesktop::CoverDesktop {

	namespace Utils {
		struct PIDAndHWND
		{
			DWORD pid;
			HWND hWnd;
		};

		HWND GetProgmanHWND();
		HWND GetDesktopWorkerW1();
		HWND GetDesktopWorkerW2();
		HWND GetHWNDFromPID(const DWORD pid);
	}

	class CoverDesktop
	{
	protected:
		HWND const hWnd;

		static std::list<CoverDesktop> instances;

		CoverDesktop(const HWND hWnd);
	public:
		static CoverDesktop GetInstance(const HWND hWnd);
		~CoverDesktop();

		bool ValidHWND() const;

		bool Cover() const;
		void Uncover() const;

		static void UncoverAll();

		bool operator==(const CoverDesktop& other) const;
	};

	std::list<CoverDesktop> CoverDesktop::instances;
}
