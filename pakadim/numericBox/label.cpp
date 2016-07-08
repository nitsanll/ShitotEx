#include "Label.h"
#include "TextBox.h"

Label::Label(int widthNew, string val) :TextBox(widthNew)
{
	//COORD c = { 7,7 };
	//width = widthNew;
	stringInput = val;
}


void Label::draw()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);
	SetConsoleCursorPosition(h, position);
	//cout << "b" << position.X << position.Y << endl;
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);
	SetText(stringInput);
	cout << stringInput;
}


