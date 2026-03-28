/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamWindow.h"
#include "../utils/DreamLogger.h"

namespace
{
	const wchar_t* DREAM_WINDOW_CLASS_NAME = L"DreamAgainEngineDXWindowClass";
}

LRESULT DreamWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DreamWindow* window = nullptr;

	if (msg == WM_NCCREATE)
	{
		// WM_NCCREATE is the first message where CreateWindowExW gives us back the
		// DreamWindow instance pointer passed through lpCreateParams.
		CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<DreamWindow*>(createStruct->lpCreateParams);

		// Store the instance pointer on the native HWND so future messages can be
		// forwarded to the correct DreamWindow object.
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else
	{
		window = reinterpret_cast<DreamWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (window != nullptr)
	{
		window->hWnd = hwnd;
		return window->HandleMessage(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

DreamWindow::DreamWindow()
	: hInstance(nullptr),
	hWnd(nullptr),
	windowTitle("DreamAgainEngineDX"),
	width(1280),
	height(720),
	isOpen(false),
	isActive(false)
{
}

DreamWindow::~DreamWindow()
{
	Destroy();
}

bool DreamWindow::RegisterWindowClass(HINSTANCE instanceHandle)
{
	WNDCLASSEXW wc = { };
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DreamWindow::WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = DREAM_WINDOW_CLASS_NAME;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	ATOM result = RegisterClassExW(&wc);
	if (result == 0)
	{
		DWORD error = GetLastError();
		if (error != ERROR_CLASS_ALREADY_EXISTS)
		{
			DreamLogger::Get().Print(LogLvl::ERR, "Failed to register the w32 window class. ERROR: ", error);
			return false;
		}
	}
	return true;
}

bool DreamWindow::Create(HINSTANCE instanceHandle, const AppConfig& config)
{
	hInstance = instanceHandle;
	width = config.windowWidth;
	height = config.windowHeight;
	windowTitle = config.WindowName;

	if (!RegisterWindowClass(hInstance)) return false;

	std::wstring wideTitle(windowTitle.begin(), windowTitle.end());

	// The final lpParam passes "this" into WM_NCCREATE so WindowProc can bind the
	// native HWND to the DreamWindow instance.
	hWnd = CreateWindowExW(
		0,
		DREAM_WINDOW_CLASS_NAME,
		wideTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		hInstance,
		this
	);

	if (hWnd == nullptr)
	{
		DWORD error = GetLastError();
		DreamLogger::Get().Print(LogLvl::ERR, "Failed to create win32 window. Error: ", error);
		return false;
	}

	isOpen = true;
	DreamLogger::Get().Print(LogLvl::INFO, "DreamWindow Create Successfully.");
	return true;
}

void DreamWindow::Show()
{
	if (hWnd == nullptr) return;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	isActive = true;
}

void DreamWindow::Destroy()
{
	if (hWnd != nullptr)
	{
		DestroyWindow(hWnd);
		hWnd = nullptr;
	}
	isOpen = false;
	isActive = false;
}

bool DreamWindow::PumpMessages()
{
	MSG msg = { };

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// WM_QUIT is the authoritative signal that the Win32 app loop should stop.
		if (msg.message == WM_QUIT)
		{
			isOpen = false;
			isActive = false;
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return isOpen;
}

LRESULT DreamWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DreamLogger::Get().LogMessage(LogLvl::INFO, "WM_CLOSE recieved. Closing DreamWindow.");
		isOpen = false;
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		DreamLogger::Get().LogMessage(LogLvl::INFO, "WM_DESTROY recieved. DreamWindow Destroyed.");
		isOpen = false;
		isActive = false;
		hWnd = nullptr;
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		return 0;

	case WM_ACTIVATE:
		isActive = (LOWORD(wParam) != WA_INACTIVE);
		return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
