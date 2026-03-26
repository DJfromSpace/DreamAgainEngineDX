/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include <chrono>

class DreamTimer {
public:
	DreamTimer();
	~DreamTimer();

	void Start();
	void Stop();
	void Tick();
	void Reset();
	
	float GetFPS();
	float GetDeltaTimeSeconds();
	float GetDeltatimeMiliSeconds();
	std::chrono::steady_clock::time_point GetPreviousFrameTime();
	bool IsTimerRunning();

private:
	float dtSecs; // delta time
	float dtMiliSecs;
	std::chrono::steady_clock::time_point previousFrameTime;
	bool timerRunning;
};