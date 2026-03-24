/* Author: DJfromSpace (Dillon E Jones) */

#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

class DreamFileSystem
{
public:
	static bool CreateDirectory(const std::string& pathName);
	static bool CreateDirectories(const std::string& pathName);

	static bool CopyFile(const std::string& startLoc, const std::string& destLoc, bool shouldOverwrite);
	static bool MoveFile(const std::string& startLoc, const std::string& destLoc, bool shouldOverwrite);

	static std::string ReadTextFile(const std::string& path);
	static bool WriteTextFile(const std::string& path, const std::string& text);

	static bool PathExists(const std::string& pathName);
	static bool IsDirectory(const std::string& path);
	static bool IsFile(const std::string& path);

	static std::string GetWorkingDir();
	static std::string GetAbsolutePath(const std::string& path);
};
