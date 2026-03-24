/* Author: DJfromSpace (Dillon E Jones) */

#include "DreamLogger.h"
#include "config.h"
#include "../io/DreamFileSystem.h"

DreamLogger::DreamLogger()
{
	Init();
}

DreamLogger::~DreamLogger()
{
	outStream.flush();
	outStream.close();
}

void DreamLogger::Init()
{
	std::cout << "Initiating DreamLogger..." << std::endl;

	std::filesystem::path logDirectory = std::filesystem::path(DREAM_PROJECT_ROOT) / "Logs";
	std::filesystem::path logPath = logDirectory / "LogFile.txt";

	DreamFileSystem::CreateDirectories(logDirectory.string());

	if (outStream.is_open())
	{
		outStream.close();
	}

	outStream.open(logPath, std::ios::out | std::ios::app);
}

void DreamLogger::LogMessage(LogLvl lvl, const std::string& log, bool printToLog)
{
	if (outStream.is_open())
	{
		switch (lvl)
		{
		case LogLvl::INFO:
			if (printToLog)
			{
				outStream << "INFO::" << log << "\n";
			}
			std::cout << "INFO::" << log << "\n";
			break;
		case LogLvl::DEBUG:
			if (printToLog)
			{
				outStream << "DEBUG::" << log << "\n";
			}
			std::cout << "DEBUG::" << log << "\n";
			break;
		case LogLvl::WARNING:
			if (printToLog)
			{
				outStream << "WARNING::" << log << "\n";
			}
			std::cout << "WARNING::" << log << "\n";
			break;
		case LogLvl::ERROR:
			if (printToLog)
			{
				outStream << "ERROR::" << log << "\n";
			}
			std::cout << "ERROR::" << log << "\n";
			break;
		default:
			std::cout << "Unknown log level:" << log << "\n";
		}
	}
	else
	{
		std::cout << "ERROR::DREAMLOGGER::Failed to open the outstream\n";
	}
}
