#include <iostream>
#include "label.h"
using namespace std;

Label::Label(char* lableText)
{
	input = lableText;
}

VOID Label::ErrorExit(LPSTR lpszMessage, HANDLE hStdin, DWORD fdwSaveOldMode)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID Label::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}

VOID Label::SetLabel(char* newInput)
{
	input = newInput;
}

char* Label::GetLabel()
{
	return input;
}

Label::~Label()
{

}