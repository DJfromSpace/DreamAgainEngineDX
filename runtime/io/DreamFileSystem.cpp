/* Author: DJfromSpace (Dillon E Jones) */

#include "DreamFileSystem.h"

bool DreamFileSystem::CreateDirectory(const std::string& pathName)
{
	return std::filesystem::create_directory(pathName);
}

bool DreamFileSystem::CreateDirectories(const std::string& pathName)
{
	return std::filesystem::create_directories(pathName);
}

bool DreamFileSystem::CopyFile(const std::string& startLoc, const std::string& destLoc, bool shouldOverwrite)
{
	if (!PathExists(startLoc)) return false;
	std::filesystem::copy_options options = shouldOverwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none;

	if (!shouldOverwrite && PathExists(destLoc)) return false;

	try
	{
		std::filesystem::copy_file(startLoc, destLoc, options);
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

bool DreamFileSystem::MoveFile(const std::string& startLoc, const std::string& destLoc, bool shouldOverwrite)
{
	if (!PathExists(startLoc)) return false;

	try
	{
		if (shouldOverwrite) std::filesystem::remove(destLoc);

		std::filesystem::rename(startLoc, destLoc);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

std::string DreamFileSystem::ReadTextFile(const std::string& pathName)
{
	std::ifstream file(pathName);
	if (!file.is_open()) return { };

	std::string text;
	std::string line;

	while (std::getline(file, line))
	{
		text += line;
		text += "\n";
	}

	return text;
}

bool DreamFileSystem::WriteTextFile(const std::string& pathName, const std::string& text)
{
	std::ofstream file(pathName);
	if (!file.is_open()) return false;

	file << text;
	return true;
}

bool DreamFileSystem::PathExists(const std::string& pathName)
{
	return std::filesystem::exists(pathName);
}

bool DreamFileSystem::IsDirectory(const std::string& pathName)
{
	return std::filesystem::is_directory(pathName);
}

bool DreamFileSystem::IsFile(const std::string& pathName)
{
	return std::filesystem::is_regular_file(pathName);
}

std::string DreamFileSystem::GetWorkingDir()
{
	return std::filesystem::current_path().string();
}

std::string DreamFileSystem::GetAbsolutePath(const std::string& pathName)
{
	return std::filesystem::absolute(pathName).string();
}

