#include "stdafx.h"
#include "ConsoleLogStream.h"

#ifdef _WIN32

#include <Windows.h>

ConsoleLogStream::ConsoleLogStream()
{
	AllocConsole();
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	freopen("CONOUT$", "w", stdout);
}

void ConsoleLogStream::putMessageIntoStream(const std::stringstream & msg)const
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	console << msg.str();
}

#elif UNIX

ConsoleLogStream::ConsoleLogStream()
{}

void ConsoleLogStream::putMessageIntoStream(const std::stringstream & msg)const
{
	console << msg.str();
}
#endif // _WIN32