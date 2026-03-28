/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

enum class LogLvl
{
	DEBUG = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3
};

class DreamLogger
{
public:
	static DreamLogger& Get(); // Singleton

	bool Init();
	const bool IsInitialized() const;
	void Shutdown();
	void LogMessage(LogLvl lvl, const std::string& log, bool printToLog = true);
	const std::string FormatFloat(double value, int precision = 4) const;

	template <typename... Args>
	void Print(LogLvl lvl, const Args&... args)
	{
		std::ostringstream messageStream;
		(messageStream << ... << args);
		LogMessage(lvl, messageStream.str(), true);
	}

private:
	DreamLogger();
	~DreamLogger();

	DreamLogger(const DreamLogger&) = delete;
	DreamLogger& operator=(const DreamLogger&) = delete;

private:
	std::ofstream outStream;
	bool initialized;
};
