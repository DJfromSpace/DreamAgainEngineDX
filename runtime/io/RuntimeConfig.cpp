/* Author: DJfromSpace (Dillon E Jones) */
#include "RuntimeConfig.h"
#include "config.h"
#include "DreamFileSystem.h"
#include "../utils/DreamLogger.h"
#include <fstream>

namespace
{
	std::string Trim(const std::string& value)
	{
		const std::string whitespace = " \t\n\r";
		const std::size_t start = value.find_first_not_of(whitespace);
		if (start == std::string::npos)
		{
			return {};
		}

		const std::size_t end = value.find_last_not_of(whitespace);
		return value.substr(start, end - start + 1);
	}
}

RuntimeConfig::RuntimeConfig()
{
	LoadConfig();
}

RuntimeConfig::~RuntimeConfig()
{
}

AppConfig RuntimeConfig::LoadConfig()
{
	DreamLogger logger;
	AppConfig appConfig;

	std::filesystem::path configPath = std::filesystem::path(DREAM_PROJECT_ROOT) / "AppConfig.txt";

	if (!DreamFileSystem::PathExists(configPath.string()))
	{
		logger.LogMessage(LogLvl::ERROR, "AppConfig.txt does not exist.");
		return appConfig;
	}

	std::ifstream inStream(configPath);
	if (!inStream.is_open())
	{
		logger.LogMessage(LogLvl::ERROR, "Failed to open AppConfig.txt");
		return appConfig;
	}

	std::string line;
	while (std::getline(inStream, line))
	{
		if (line.empty() || line.at(0) == '#')
		{
			continue;
		}

		std::size_t equalPos = line.find('=');
		if (equalPos == std::string::npos)
		{
			logger.Print(LogLvl::WARNING, "Invlaid config line: ", line);
			continue;
		}

		std::string key = Trim(line.substr(0, equalPos));
		std::string value = Trim(line.substr(equalPos + 1));

		if (key == "windowWidth")
		{
			appConfig.windowWidth = std::stoi(value);
		}
		else if (key == "windowHeight")
		{
			appConfig.windowHeight = std::stoi(value);
		}
		else if (key == "fullscreen")
		{
			appConfig.fullscreen = (value == "true" || value == "1");
		}
		else if (key == "AppName")
		{
			appConfig.AppName = value;
		}
		else if (key == "WindowName")
		{
			appConfig.WindowName = value;
		}
		else
		{
			logger.Print(LogLvl::WARNING, "Unknown config key: ", key);
		}

		logger.Print(LogLvl::INFO, "Key: ", key, " Value: ", value);
	}

	return appConfig;
}
