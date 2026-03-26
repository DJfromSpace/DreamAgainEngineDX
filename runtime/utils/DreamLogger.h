/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

enum class LogLvl{
	DEBUG = 0,
	INFO = 1,
	WARNING = 2,
	ERROR = 3
};

class DreamLogger
{
public:
	static bool Init();
	static bool IsInitialized();
	static void Shutdown();
	static void LogMessage(LogLvl lvl, const std::string& log, bool printToLog = true);
	static std::string FormatFloat(double value, int precision = 4);

	template <typename... Args>
	static void Print(LogLvl lvl, const Args&... args)
	{
		std::ostringstream messageStream;
		(messageStream << ... << args);
		LogMessage(lvl, messageStream.str(), true);
	}

private:
	static std::ofstream outStream;
	static bool initialized;
};
