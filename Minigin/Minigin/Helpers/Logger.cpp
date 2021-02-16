#include "MiniginPCH.h"
#include "Logger.h"
#include <consoleapi2.h>
#include <processenv.h>

bool JKEngine::Logger::m_IsInitialized = false;
HANDLE JKEngine::Logger::m_ConsoleHandle = {};

void JKEngine::Logger::Init()
{
	//Source for this Initialize: OverlordEngine Logger.cpp
#if defined(DEBUG) | defined(_DEBUG)
	//Create Console Window
	if (AllocConsole() && !m_IsInitialized)
	{
		//Redirect standard in error and out to manually created console
		FILE* pCout;
		freopen_s(&pCout, "CONIN$", "r", stdin);
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		freopen_s(&pCout, "CONOUT$", "w", stderr);

		//Fix known issues with creating console(clear buffers)
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();

		//Get Handle of the new console
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		//Disable the close button of the console
		HWND hwnd = GetConsoleWindow();
		if (hwnd != NULL)
		{
			HMENU hMenu = GetSystemMenu(hwnd, FALSE);
			if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		}
		m_IsInitialized = true;
	}
#endif
}

void JKEngine::Logger::Log(LogLevel level, const std::string& msg)
{
	switch (level)
	{
	case LogLevel::Info:
		LogInfo(msg);
		break;
	case LogLevel::Warning:
		LogWarning(msg);
		break;
	case LogLevel::Error:
		LogError(msg);
		break;
	default:
		LogInfo(msg);
		break;
	}
}

void JKEngine::Logger::LogInfo(const std::string& msg)
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "[INFO] : " << msg << std::endl;
	std::cout.flush();
}

void JKEngine::Logger::LogWarning(const std::string& msg)
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "[WARNING] : " << msg << std::endl;
	std::cout.flush();
}

void JKEngine::Logger::LogError(const std::string& msg)
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << "[ERROR] : " << msg << std::endl;
	std::cout.flush();
}
