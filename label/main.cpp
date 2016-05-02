#include "label.h"
#include <iostream>
using namespace std;

DWORD fdwSaveOldMode;
HANDLE hStdin;

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	Label label("label");
	
	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		label.ErrorExit("GetStdHandle", hStdin, fdwSaveOldMode);

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		label.ErrorExit("GetConsoleMode", hStdin, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		label.ErrorExit("SetConsoleMode", hStdin, fdwSaveOldMode);

	// Loop to read and handle the next 100 input events. 

	while (counter++ <= 100)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			label.ErrorExit("ReadConsoleInput", hStdin, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 
		
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				break;

			case MOUSE_EVENT: // mouse input 				 
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				label.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			default:
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}
