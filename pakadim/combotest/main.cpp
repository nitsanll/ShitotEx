#include <windows.h>
#include <stdio.h>
#include "combobox.h"

HANDLE hStdin;
HANDLE hStdout;
DWORD fdwSaveOldMode;
int line = 7;

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	Combo* combo = new Combo({ "1990", "1991", "1992", "1993" });

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		combo->ErrorExit("GetStdHandle", hStdin, fdwSaveOldMode);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		combo->ErrorExit("GetConsoleMode", hStdin, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		combo->ErrorExit("SetConsoleMode", hStdin, fdwSaveOldMode);

	while (counter++ != EOF)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			combo->ErrorExit("ReadConsoleInput", hStdin, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				combo->KeyEventProc(irInBuf[i].Event.KeyEvent, hStdout, line);
				break;

			case MOUSE_EVENT: // mouse input 
				combo->MouseEventProc(irInBuf[i].Event.MouseEvent, hStdout, line);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				combo->ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			default:
				//combo->ErrorExit("Unknown event type", hStdin, fdwSaveOldMode);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}