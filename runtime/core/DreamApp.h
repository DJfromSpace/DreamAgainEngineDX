/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include "../utils/DreamLogger.h"
#include "AppConfig.h"

class DreamApp
{
public:
	DreamApp();
	~DreamApp();

	bool Init();

	void TestFunc();

public:
	AppConfig appConfig;
};
