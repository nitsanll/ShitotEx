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
	int startCoord = 7;

	COORD c = { startCoord, startCoord };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);
	SetConsoleCursorPosition(h, c);

	printf("%c%c%c%c%c%c%c%c\n", '\xDA', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xBF');

	c = { startCoord, startCoord + 1 };
	SetConsoleCursorPosition(h, c);

	printf("%c label%c\n", '\xB3', '\xB3');

	c = { startCoord, startCoord + 2 };
	SetConsoleCursorPosition(h, c);

	printf("%c%c%c%c%c%c%c%c\n", '\xC0', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xD9');

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);



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
							//KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input 
							  //MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				label.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				label.ErrorExit("Unknown event type", hStdin, fdwSaveOldMode);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}
