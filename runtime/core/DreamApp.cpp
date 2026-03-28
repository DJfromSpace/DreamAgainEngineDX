/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamApp.h"
#include "../io/RuntimeConfig.h"
#include "../io/DreamFileSystem.h"

DreamApp::DreamApp()
{
}

DreamApp::~DreamApp()
{
}

bool DreamApp::Init()
{
	if (!DreamLogger::Get().Init()) return false;

	RuntimeConfig rConfig;
	if(!rConfig.LoadConfig(appConfig)) return false;

	HINSTANCE instanceHandle = GetModuleHandleW(nullptr);
	if (instanceHandle == nullptr)
	{
		DreamLogger::Get().LogMessage(LogLvl::ERR, "Failed to get the window module handle.");
		return false;
	}
	if (!window.Create(instanceHandle, appConfig))
	{
		DreamLogger::Get().LogMessage(LogLvl::ERR, "Failed to create DreamWindow.");
		return false;
	}

	window.Show();
	DreamLogger::Get().LogMessage(LogLvl::INFO, "DreamApp Init Successful.");
	return true;
}

void DreamApp::Run()
{
	DreamLogger::Get().LogMessage(LogLvl::INFO, "Starting DreamApp window loop.");

	while (window.IsOpen())
	{
		if (!window.PumpMessages())
		{
			break;
		}
	}

	DreamLogger::Get().LogMessage(LogLvl::INFO, "DreamApp Window loop ended.");
}


