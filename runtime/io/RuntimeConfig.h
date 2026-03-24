/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include "../core/AppConfig.h"

class RuntimeConfig
{
public:
	RuntimeConfig();
	~RuntimeConfig();

	AppConfig LoadConfig();
};