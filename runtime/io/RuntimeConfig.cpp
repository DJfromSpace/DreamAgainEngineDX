/* Author: DJfromSpace (Dillon E Jones) */
#include "RuntimeConfig.h"
#include "DreamFileSystem.h"
#include "../utils/DreamLogger.h"
#include <fstream>
#include <optional>

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

	std::optional<int> TryParseInt(const std::string& value)
	{
		try
		{
			std::size_t parsedChars = 0;
			const int parsedValue = std::stoi(value, &parsedChars);

			if (parsedChars != value.size())
			{
				return std::nullopt;
			}

			return parsedValue;
		}
		catch (...)
		{
			return std::nullopt;
		}
	}

	std::optional<bool> TryParseBool(const std::string& value)
	{
		if (value == "true" || value == "1")
		{
			return true;
		}

		if (value == "false" || value == "0")
		{
			return false;
		}

		return std::nullopt;
	}

	std::string NormalizeQuotedString(const std::string& value)
	{
		if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
		{
			return value.substr(1, value.size() - 2);
		}

		return value;
	}
}

RuntimeConfig::RuntimeConfig()
{
}

RuntimeConfig::~RuntimeConfig()
{
}

bool RuntimeConfig::LoadConfig(AppConfig& appConfig)
{
	if (!DreamFileSystem::PathExists(DreamFileSystem::GetAppConfigPath().string()))
	{
		DreamLogger::Get().LogMessage(LogLvl::ERR, "AppConfig.txt does not exist. Using defaults.");
		return false;
	}

	std::ifstream inStream(DreamFileSystem::GetAppConfigPath());
	if (!inStream.is_open())
	{
		DreamLogger::Get().LogMessage(LogLvl::ERR, "Failed to open AppConfig.txt. Using defaults.");
		return false;
	}

	std::string line;
	int lineNumber = 0;
	while (std::getline(inStream, line))
	{
		++lineNumber;

		const std::string trimmedLine = Trim(line);
		if (trimmedLine.empty() || trimmedLine[0] == '#')
		{
			continue;
		}

		const std::size_t equalPos = trimmedLine.find('=');
		if (equalPos == std::string::npos)
		{
			DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": invalid config line, missing '='. Using defaults for that line.");
			continue;
		}

		const std::string key = Trim(trimmedLine.substr(0, equalPos));
		const std::string value = Trim(trimmedLine.substr(equalPos + 1));

		if (key.empty())
		{
			DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": empty config key. Using defaults for that line.");
			continue;
		}

		if (value.empty())
		{
			DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": empty value for key '", key, "'. Using default.");
			continue;
		}

		if (key == "windowWidth")
		{
			const std::optional<int> parsedValue = TryParseInt(value);
			if (!parsedValue || *parsedValue <= 0)
			{
				DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": invalid windowWidth value '", value, "'. Using default.");
				continue;
			}

			appConfig.windowWidth = *parsedValue;
		}
		else if (key == "windowHeight")
		{
			const std::optional<int> parsedValue = TryParseInt(value);
			if (!parsedValue || *parsedValue <= 0)
			{
				DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": invalid windowHeight value '", value, "'. Using default.");
				continue;
			}

			appConfig.windowHeight = *parsedValue;
		}
		else if (key == "fullscreen")
		{
			const std::optional<bool> parsedValue = TryParseBool(value);
			if (!parsedValue.has_value())
			{
				DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": invalid fullscreen value '", value, "'. Use true/false/1/0. Using default.");
				continue;
			}

			appConfig.fullscreen = *parsedValue;
		}
		else if (key == "AppName")
		{
			if (value.size() < 2 || value.front() != '"' || value.back() != '"')
			{
				DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": AppName must be wrapped in quotes. Using default.");
				continue;
			}

			appConfig.AppName = NormalizeQuotedString(value);
		}
		else if (key == "WindowName")
		{
			if (value.size() < 2 || value.front() != '"' || value.back() != '"')
			{
				DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": WindowName must be wrapped in quotes. Using default.");
				continue;
			}

			appConfig.WindowName = NormalizeQuotedString(value);
		}
		else
		{
			DreamLogger::Get().Print(LogLvl::WARNING, "Line ", lineNumber, ": unknown config key '", key, "'. Ignoring.");
		}
	}

	return true;
}
