/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamTimer.h"

DreamTimer::DreamTimer() : dtSecs(0), dtMiliSecs(0), timerRunning(false), previousFrameTime(std::chrono::steady_clock::now())
{
}

DreamTimer::~DreamTimer()
{
}

void DreamTimer::Start()
{
	timerRunning = true;
	previousFrameTime = std::chrono::steady_clock::now();
	dtSecs = 0;
	dtMiliSecs = 0;
}

void DreamTimer::Stop()
{
	timerRunning = false;
}

void DreamTimer::Tick()
{
	if (!timerRunning)
	{
		Start();
	}
	// Capture now
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration diff = currentTime - previousFrameTime;
	dtSecs = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1, 1>>>(diff).count(); // Convert to Seconds
	dtMiliSecs = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(diff).count(); // Convert to Miliseconds
	previousFrameTime = currentTime;
}

void DreamTimer::Reset()
{
	dtSecs = 0;
	dtMiliSecs = 0;
	timerRunning = false;
	previousFrameTime = std::chrono::steady_clock::now();
}

float DreamTimer::GetFPS()
{
	if (dtSecs <= 0.000000000001f)
	{
		return 0.0f;
	}
	return 1.0f / dtSecs;
}

float DreamTimer::GetDeltaTimeSeconds()
{
	return dtSecs;
}

float DreamTimer::GetDeltatimeMiliSeconds()
{
	return dtMiliSecs;
}

std::chrono::steady_clock::time_point DreamTimer::GetPreviousFrameTime()
{
	return previousFrameTime;
}

bool DreamTimer::IsTimerRunning()
{
	return timerRunning;
}
