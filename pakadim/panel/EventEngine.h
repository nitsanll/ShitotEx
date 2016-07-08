#include "iControl.h"
#include <Windows.h>

class EventEngine
{
public:
	EventEngine(DWORD input = STD_INPUT_HANDLE, DWORD output = STD_OUTPUT_HANDLE);
	void run(iControl &c); //calls draw and key and mouse events
	virtual ~EventEngine();
private:
	void moveFocus(iControl &main, iControl *focused); //change the focus to the next control that can have it
	Graphics _graphics;
	HANDLE _console;
	DWORD _consoleMode;
};