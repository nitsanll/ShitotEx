#include "TextBox.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	short startCoord = 7;
	short maxCoord = 14;

	TextBox textbox;
	iControl* control = &textbox;
	COORD c = { startCoord, startCoord };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		textbox.ErrorExit("GetStdHandle", hStdin, fdwSaveOldMode);

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		textbox.ErrorExit("GetConsoleMode", hStdin, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		textbox.ErrorExit("SetConsoleMode", hStdin, fdwSaveOldMode);

	// Loop to read and handle the next 100 input events. 

	while (counter++ != EOF)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			textbox.ErrorExit("ReadConsoleInput", hStdin, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				textbox.KeyEventProc(irInBuf[i].Event.KeyEvent, h, startCoord);
				break;

			case MOUSE_EVENT: // mouse input 
				textbox.MouseEventProc(irInBuf[i].Event.MouseEvent, h, startCoord);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				textbox.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				textbox.ErrorExit("Unknown event type", hStdin, fdwSaveOldMode);
				break;
			}
		}
	}


	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

