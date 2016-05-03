#include "iControl.h"
#include <Windows.h>
#include <iostream>

using namespace std;

void iControl::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}

void iControl::ErrorExit(LPSTR lpszMessage, HANDLE hStdin, DWORD fdwSaveOldMode)
{
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}