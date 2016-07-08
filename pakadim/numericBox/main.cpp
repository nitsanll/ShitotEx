#include <windows.h>
#include <stdio.h>
#include "numericBox.h"

HANDLE hStdin;
HANDLE hStdout;
DWORD fdwSaveOldMode;

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	Panel p(20, 30);
	NumericBox num(7, 1, 5);

	p.AddiControl(num, 2, 3);
	p.draw();

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		num.ErrorExit("GetStdHandle", hStdin, fdwSaveOldMode);

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		num.ErrorExit("GetConsoleMode", hStdin, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		num.ErrorExit("SetConsoleMode", hStdin, fdwSaveOldMode);

	while (counter++ != EOF)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			num.ErrorExit("ReadConsoleInput", hStdin, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				//num.KeyEventProc(irInBuf[i].Event.KeyEvent, hStdout);
				break;

			case MOUSE_EVENT: // mouse input 
				num.MouseEventProc(irInBuf[i].Event.MouseEvent, hStdout);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				num.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			default:
				//num->ErrorExit("Unknown event type", hStdin, fdwSaveOldMode);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}
