#include <iostream>
#include "label.h"
using namespace std;

Label::Label(char* lableText) :iControl({ 7,7 }, { 100,100 })
{
	input = lableText;
	draw();
}

VOID Label::SetLabel(char* newInput)
{
	input = newInput;
}

char* Label::GetLabel()
{
	return input;
}

void Label::draw()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);
	SetConsoleCursorPosition(h, position);
	
	printf("%c%c%c%c%c%c%c%c\n", '\xDA', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xBF');

	COORD c = { position.X, position.Y + 1 };
	SetConsoleCursorPosition(h, c);

	printf("%c label%c\n", '\xB3', '\xB3');

	c = { position.X, position.Y + 2 };
	SetConsoleCursorPosition(h, c);

	printf("%c%c%c%c%c%c%c%c\n", '\xC0', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xC4', '\xD9');

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
}
