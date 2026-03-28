/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include <string>
#include <windows.h>
#include "AppConfig.h"

class DreamWindow
{
public:
	DreamWindow();
	~DreamWindow();

	bool Create(HINSTANCE instanceHandle, const AppConfig& config);
	void Show();
	void Destroy();
	bool PumpMessages();

	bool IsOpen() const { return isOpen; }
	bool IsActive() const { return isActive; }
	HWND GetHandle() const { return hWnd; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	const std::string& GetTitle() const { return windowTitle; }

private:
	bool RegisterWindowClass(HINSTANCE instanceHandle);
	LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	HWND hWnd;
	std::string windowTitle;
	int width;
	int height;
	bool isOpen;
	bool isActive;
};
