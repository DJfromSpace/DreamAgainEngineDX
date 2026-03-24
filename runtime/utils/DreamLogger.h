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
	DreamLogger();
	~DreamLogger();

	void Init();
	void LogMessage(LogLvl lvl, const std::string& log, bool printToLog = true);

	template <typename... Args>
	void Print(LogLvl lvl, const Args&... args)
	{
		std::ostringstream messageStream;
		(messageStream << ... << args);
		LogMessage(lvl, messageStream.str(), true);
	}

private:
	std::ofstream outStream;
};
