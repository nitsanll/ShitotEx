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
	TextBox textbox;
	int startCoord = 7;
	int maxCoord = 14;

	COORD c = { startCoord, startCoord };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);

	DWORD wAttr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(h, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	SetConsoleTextAttribute(h, wAttr2);

	printf("%c%c%c%c%c%c%c%c\n", '\xDA', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xBF');

	c = { startCoord, startCoord + 1 };
	SetConsoleCursorPosition(h, c);

	printf("%c\n", '\xB3');


	c = { maxCoord, startCoord + 1 };
	SetConsoleCursorPosition(h, c);

	printf("%c\n", '\xB3');

	c = { startCoord, startCoord + 2 };
	SetConsoleCursorPosition(h, c);

	printf("%c%c%c%c%c%c%c%c\n", '\xC0', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xD9');

	CONSOLE_CURSOR_INFO cci = { 10, TRUE };
	SetConsoleCursorInfo(h, &cci);

	c = { startCoord + 1, startCoord + 1 };
	SetConsoleCursorPosition(h, c);

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
				textbox.KeyEventProc(irInBuf[i].Event.KeyEvent, h, &textbox);
				break;

			case MOUSE_EVENT: // mouse input 
				textbox.MouseEventProc(irInBuf[i].Event.MouseEvent, h);
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

