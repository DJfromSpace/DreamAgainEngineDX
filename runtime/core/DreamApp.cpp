/* Author: DJfromSpace (Dillon E Jones) */
#include "DreamApp.h"
#include "../io/RuntimeConfig.h"
#include "../io/DreamFileSystem.h"

DreamApp::DreamApp()
{
}

DreamApp::~DreamApp()
{
}

bool DreamApp::Init()
{
	if (!DreamLogger::Init()) return false;

	RuntimeConfig rConfig;
	if(!rConfig.LoadConfig(appConfig)) return false;

	return true;
}

void DreamApp::TestFunc()
{
	DreamLogger::LogMessage(LogLvl::INFO, "Hello TikTok/Youtube!");
	DreamLogger::LogMessage(LogLvl::INFO, "Testing AppStartup");

	std::string dir = DreamFileSystem::GetLogDirPath().string();
	std::string file = DreamFileSystem::GetLogDirPath().string() + "/test.txt";
	std::string copy = DreamFileSystem::GetLogDirPath().string() + "/test_copy.txt";

	DreamLogger::Print(LogLvl::INFO, "Creating Dirs: ", DreamFileSystem::CreateDirectories(dir));
	DreamLogger::Print(LogLvl::INFO, "Creating Dir: ", DreamFileSystem::CreateDirectory(dir));
	DreamLogger::Print(LogLvl::INFO, "Writing File: ", DreamFileSystem::WriteTextFile(file, "DreamFileSystem check success!"));
	DreamLogger::Print(LogLvl::INFO, "Path Exists File: ", DreamFileSystem::PathExists(file));
	DreamLogger::Print(LogLvl::INFO, "Path Exists Dir: ", DreamFileSystem::PathExists(dir));
	DreamLogger::Print(LogLvl::INFO, "Is File: ", DreamFileSystem::IsFile(file));
	DreamLogger::Print(LogLvl::INFO, "Read File: ", DreamFileSystem::ReadTextFile(file));
	DreamLogger::Print(LogLvl::INFO, "Copy File: ", DreamFileSystem::CopyFile(file, copy, true));
	DreamLogger::Print(LogLvl::INFO, "Working Dir: ", DreamFileSystem::GetWorkingDir());
	DreamLogger::Print(LogLvl::INFO, "Project Root: ", DreamFileSystem::GetProjectDirPath().string());


	DreamLogger::Print(LogLvl::INFO, "WindowName: ", appConfig.WindowName);
	DreamLogger::Print(LogLvl::INFO, "AppName: ", appConfig.AppName);
	DreamLogger::Print(LogLvl::INFO, "windowWidth: ", appConfig.windowWidth);
	DreamLogger::Print(LogLvl::INFO, "windowHeight: ", appConfig.windowHeight);
	DreamLogger::Print(LogLvl::INFO, "fullscreen: ", appConfig.fullscreen);
}
