/* Author: DJfromSpace (Dillon E Jones) */

#pragma once
#include <string>

struct AppConfig {
	int windowWidth = 1280;
	int windowHeight = 720;
	bool fullscreen = false;
	std::string AppName = "DefaultAppName";
	std::string WindowName = "DefaultWindowName";
};
