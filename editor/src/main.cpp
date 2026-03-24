/* Author: DJfromSpace (Dillon E Jones) */

#include <iostream>
#include <string>
#include "config.h"
#include "../../runtime/io/DreamFileSystem.h"
#include "../../runtime/utils/DreamLogger.h"
#include "../../runtime/core/AppConfig.h"
#include "../../runtime/io/RuntimeConfig.h"

int main()
{
	DreamLogger logger;
	AppConfig appConfig;
	RuntimeConfig rConfig;

	logger.LogMessage(LogLvl::INFO, "Hello TikTok/Youtube!");
	logger.LogMessage(LogLvl::INFO, "Testing DreamFileSystem");

	std::string projectRoot = DREAM_PROJECT_ROOT;
	std::string dir = projectRoot + "/Logs";
	std::string file = projectRoot + "/Logs/test.txt";
	std::string copy = projectRoot + "/Logs/test_copy.txt";

	logger.Print(LogLvl::INFO, "Creating Dirs: ", DreamFileSystem::CreateDirectories(dir));
	logger.Print(LogLvl::INFO, "Creating Dir: ", DreamFileSystem::CreateDirectory(dir));
	logger.Print(LogLvl::INFO, "Writing File: ", DreamFileSystem::WriteTextFile(file, "DreamFileSystem check success!"));
	logger.Print(LogLvl::INFO, "Path Exists File: ", DreamFileSystem::PathExists(file));
	logger.Print(LogLvl::INFO, "Path Exists Dir: ", DreamFileSystem::PathExists(dir));
	logger.Print(LogLvl::INFO, "Is File: ", DreamFileSystem::IsFile(file));
	logger.Print(LogLvl::INFO, "Read File: ", DreamFileSystem::ReadTextFile(file));
	logger.Print(LogLvl::INFO, "Copy File: ", DreamFileSystem::CopyFile(file, copy, true));
	logger.Print(LogLvl::INFO, "Working Dir: ", DreamFileSystem::GetWorkingDir());
	logger.Print(LogLvl::INFO, "Project Root: ", projectRoot);

	appConfig = rConfig.LoadConfig();

	logger.Print(LogLvl::INFO, "WindowName: ", appConfig.WindowName);
	logger.Print(LogLvl::INFO, "AppName: ", appConfig.AppName);
	logger.Print(LogLvl::INFO, "windowWidth: ", appConfig.windowWidth);
	logger.Print(LogLvl::INFO, "windowHeight: ", appConfig.windowHeight);
	logger.Print(LogLvl::INFO, "fullscreen: ", appConfig.fullscreen);


	return 0;
}
