/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamApp.h"
#include "../debugtools/DreamDebugTools.h"
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

	return true;
}

void DreamApp::Run()
{
	float totalElaspedSeconds = 0.0f;
	float timeSinceLastPrint = 0.0f;
	float printIntervalSeconds = 1.0f;
	float maxRunSeconds = 5.0f;
	int framesSinceLastPrint = 0;
	timer.Start();

	DreamLogger::Get().LogMessage(LogLvl::INFO, "Starting Day 4 frame timing run.");
	while (totalElaspedSeconds < maxRunSeconds)
	{
		timer.Tick();
		float frameDelta = timer.GetDeltaTimeSeconds();
		totalElaspedSeconds += frameDelta;
		timeSinceLastPrint += frameDelta;
		++framesSinceLastPrint;

		if (timeSinceLastPrint >= printIntervalSeconds && framesSinceLastPrint > 0)
		{
			DreamDebugTools::LogTimingSummary(totalElaspedSeconds, timeSinceLastPrint, framesSinceLastPrint);
			timeSinceLastPrint = 0.0f;
			framesSinceLastPrint = 0;
		}
	}

	timer.Stop();
	DreamLogger::Get().Print(LogLvl::INFO, "Frame timing run complete after ", DreamLogger::Get().FormatFloat(totalElaspedSeconds), " seconds.");
}


