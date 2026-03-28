/* Author: DJfromSpace (Dillon E Jones) */

#include "DreamLogger.h"
#include "../io/DreamFileSystem.h"

DreamLogger::DreamLogger(): initialized(false)
{ }

DreamLogger::~DreamLogger()
{
	Shutdown();
}

DreamLogger& DreamLogger::Get()
{
	static DreamLogger logger;
	return logger;
}

bool DreamLogger::Init()
{
	if (initialized)
	{
		return true;
	}

	std::cout << "Initiating DreamLogger..." << std::endl;

	std::filesystem::path logPath = DreamFileSystem::GetLogDirPath() / "LogFile.txt";
	if (!DreamFileSystem::PathExists(DreamFileSystem::GetLogDirPath().string()) &&
		!DreamFileSystem::CreateDirectories(DreamFileSystem::GetLogDirPath().string()))
	{
		std::cout << "ERROR::DREAMLOGGER::The filesystem failed to create the log directory\n";
		return false;
	}

	if (outStream.is_open())
	{
		outStream.close();
	}

	outStream.open(logPath, std::ios::out | std::ios::app);
	initialized = outStream.is_open();

	if (!initialized)
	{
		std::cout << "ERROR::DREAMLOGGER::Failed to open the outstream\n";
		return false;
	}

	return true;
}

bool DreamLogger::IsInitialized() const
{
	return initialized;
}

void DreamLogger::Shutdown()
{
	if (outStream.is_open())
	{
		outStream.flush();
		outStream.close();
	}

	initialized = false;
}

void DreamLogger::LogMessage(LogLvl lvl, const std::string& log, bool printToLog)
{
	if (!initialized && !Init())
	{
		std::cout << "ERROR::DREAMLOGGER::Logger is not initialized\n";
		return;
	}

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
		case LogLvl::ERR:
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

std::string DreamLogger::FormatFloat(double value, int precision) const
{
	std::ostringstream stream;
	stream.setf(std::ios::fixed, std::ios::floatfield);
	stream.precision(precision);
	stream << value;
	return stream.str();
}
