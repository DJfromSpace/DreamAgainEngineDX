/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include "../utils/DreamLogger.h"
#include "AppConfig.h"
#include "DreamTimer.h"
#include "DreamWindow.h"

class DreamApp
{
public:
	DreamApp();
	~DreamApp();

	bool Init();
	void Run();

public:
	AppConfig appConfig;
	DreamTimer timer;
	DreamWindow window;
};
