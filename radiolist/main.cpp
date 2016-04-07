#include <windows.h>
#include <iostream>
#include <string>
#include "radioList.h"

using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;


int main() {

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	int startLine = 7;
	int newLineY = startLine;
	int clicked = 0;

	vector<string> myList = { "[ ]hello", "[ ] hi", "[ ]love" };
	//myList.insert("[]hello", 0);
	RadioList RadioList(myList);

	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);

	for (int i = 0; i < RadioList.GetList().size(); i++)
	{
		c = { startLine, newLineY++ };
		SetConsoleCursorPosition(h, c);
		cout << RadioList.GetList()[i] << endl;
	}



	//	CONSOLE_SCREEN_BUFFER_INFO cbi;
	//	GetConsoleScreenBufferInfo(h, &cbi);
	//	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	//	SetConsoleTextAttribute(h, wAttr2);

	CONSOLE_CURSOR_INFO cci = { 10, TRUE };
	SetConsoleCursorInfo(h, &cci);

	c = { startLine + 1, startLine };
	SetConsoleCursorPosition(h, c);

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		RadioList.ErrorExit("GetStdHandle", hStdin, fdwSaveOldMode);

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		RadioList.ErrorExit("GetConsoleMode", hStdin, fdwSaveOldMode);

	// Enable the window and mouse input events. 

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		RadioList.ErrorExit("SetConsoleMode", hStdin, fdwSaveOldMode);



	while (counter++ != EOF)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			RadioList.ErrorExit("ReadConsoleInput", hStdin, fdwSaveOldMode);

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{

			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				RadioList.KeyEventProc(irInBuf[i].Event.KeyEvent, h, startLine, &RadioList);
				break;

			case MOUSE_EVENT: // mouse input 
				RadioList.MouseEventProc(irInBuf[i].Event.MouseEvent, h, startLine, &RadioList);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				RadioList.ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events 
				break;
			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				RadioList.ErrorExit("Unknown event type", hStdin, fdwSaveOldMode);
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);



	return 0;
}