#include <windows.h>
#include <iostream>
#include <string>
#include "checkList.h"


using namespace std;

HANDLE hStd;
DWORD fdwSaveOldMode;


int main() {

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	int startLine = 7;
	int newLineY = startLine;
	int clicked = 0;

	CheckList checklist;


	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the standard input handle. 

	hStd = GetStdHandle(STD_INPUT_HANDLE);
	if (hStd == INVALID_HANDLE_VALUE)
		checklist.ErrorExit("GetStdHandle", hStd, fdwSaveOldMode);

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStd, &fdwSaveOldMode))
		checklist.ErrorExit("GetConsoleMode", hStd, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStd, fdwMode))
		checklist.ErrorExit("SetConsoleMode", hStd, fdwSaveOldMode);



	while (counter++ != EOF)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStd,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			checklist.ErrorExit("ReadConsoleInput", hStd, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{

			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				checklist.KeyEventProc(irInBuf[i].Event.KeyEvent, h, startLine);
				break;

			case MOUSE_EVENT: // mouse input 
				checklist.MouseEventProc(irInBuf[i].Event.MouseEvent, h, startLine);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				checklist.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 
				break;
			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				checklist.ErrorExit("Unknown event type", hStd, fdwSaveOldMode);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStd, fdwSaveOldMode);



	return 0;
}