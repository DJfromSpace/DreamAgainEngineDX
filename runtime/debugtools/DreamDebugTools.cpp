/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamDebugTools.h"
#include "../utils/DreamLogger.h"

void DreamDebugTools::LogTimingSummary(float totalElapsedSeconds, float intervalElapsedSeconds, int framesSinceLastPrint)
{
	if (intervalElapsedSeconds <= 0.0f || framesSinceLastPrint <= 0)
	{
		return;
	}

	const float averageFrameTimeMs = (intervalElapsedSeconds / static_cast<float>(framesSinceLastPrint)) * 1000.0f;
	const float averageFps = static_cast<float>(framesSinceLastPrint) / intervalElapsedSeconds;

	DreamLogger::Get().Print(LogLvl::INFO, "Elapsed (s): ", DreamLogger::Get().FormatFloat(totalElapsedSeconds));
	DreamLogger::Get().Print(LogLvl::INFO, "Average Frame Time (ms): ", DreamLogger::Get().FormatFloat(averageFrameTimeMs));
	DreamLogger::Get().Print(LogLvl::INFO, "Average FPS: ", DreamLogger::Get().FormatFloat(averageFps));
}
