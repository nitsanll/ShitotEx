#include "Combobox.h"

Combo::Combo(int width, vector<string> entries) :Panel(width, entries.size()+1)
{
	list = entries;
	deafult = "   ";
	Label l(width - 1, deafult);
	Button b(1);
	b.SetText("v");
	label = l;
	button = b;
}

vector<string> Combo::getList()
{
	return list;
}

size_t Combo::GetSelectedIndex()
{
	for (int i = 0; i < list.size(); i++)
	{
		if (deafult.compare(list.at(i)) == 0) {
			return i;
		}
	}
}
void Combo::SetSelectedIndex(size_t index){
	deafult = list.at(index);
}

void Combo::draw()
{	
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	
	c[list.size()+1] = {};
	COORD tmpPos = position;
	for (int i = 0; i<=list.size(); i++)
	{
		c[i] = tmpPos;
		tmpPos.Y++;
	}

	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hStdout, wAttr1);

	SetConsoleCursorPosition(hStdout, c[0]);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);
	AddiControl(label, position.X, position.Y);
	AddiControl(button, position.X + (width - 1), position.Y);
	controls.at(0)->draw();//label draw
	controls.at(1)->draw();//button1 draw

	SetConsoleCursorPosition(hStdout, c[0]);
}

void Combo::MouseEventProc(MOUSE_EVENT_RECORD mer, HANDLE hStdout)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	DWORD wAttr2 = cbi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	DWORD wAttr3 = cbi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	DWORD wAttr4 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	string erase = "                                          ";
	if (mer.dwEventFlags == 0)
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			vector<string> str = list;
			if (mer.dwMousePosition.Y == getLine() && mer.dwMousePosition.X >= position.X && mer.dwMousePosition.X <= position.X+size.X)
			{
				printLines(hStdout, wAttr1, wAttr2);
			}

			for (int i = 0, j = 1; i < str.size(); i++, j++) {
				if (mer.dwMousePosition.Y == getLine() + j && mer.dwMousePosition.X >= position.X && mer.dwMousePosition.X <= position.X + size.X)
				{
					SetSelectedIndex(i);
					SetConsoleCursorPosition(hStdout, position);
					SetConsoleTextAttribute(hStdout, wAttr1);
					label.SetText(deafult);
					label.draw();
					SetConsoleCursorPosition(hStdout, c[1]);
					eraseLines(str.size(), hStdout);
					SetConsoleCursorPosition(hStdout, position);
				}
			}
		}
	}
}

void Combo::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hStdout)
{
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	COORD coord = cbi.dwCursorPosition;
	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	DWORD wAttr2 = cbi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	DWORD wAttr3 = cbi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	DWORD wAttr4 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	string erase = "                   ";

	const WORD up = VK_UP;
	const WORD down = VK_DOWN;
	const WORD enter = VK_RETURN;
	if (ker.bKeyDown) {
		if (ker.wVirtualKeyCode == up)
		{
			GetConsoleScreenBufferInfo(hStdout, &cbi);
			coord = cbi.dwCursorPosition;
			for (int i = list.size(); i > 0; i--)
			{
				if (coord.Y == c[i].Y) {
					changeTextColorUp(i-1, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
				}
			}
		}

		if (ker.wVirtualKeyCode == down)
		{
			if (coord.Y == getLine())
			{
				printLines(hStdout, wAttr1, wAttr2);
				changeTextColorDown(0, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
			}

			else
			{
				GetConsoleScreenBufferInfo(hStdout, &cbi);
				coord = cbi.dwCursorPosition;
				printLines(hStdout, wAttr1, wAttr2);
				for (int i = 1; i <= list.size(); i++)
				{
					if (coord.Y == c[i].Y) {
						changeTextColorDown(i, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
					}
				}
			}
		}

		if (ker.wVirtualKeyCode == enter)
		{
			GetConsoleScreenBufferInfo(hStdout, &cbi);
			coord = cbi.dwCursorPosition;
			int i = coord.Y;
			for (int j = 1; j <= list.size(); j++)
			{
				if (i == c[j].Y) {
					SetSelectedIndex(j - 1);
					SetConsoleCursorPosition(hStdout, position);
					SetConsoleTextAttribute(hStdout, wAttr1);
					label.SetText(deafult);
					label.draw();
					SetConsoleCursorPosition(hStdout, c[1]);
					eraseLines(list.size(), hStdout);
					SetConsoleCursorPosition(hStdout, position);
				}
			}

		}
	}
}

void Combo::printLines(HANDLE hStdout, DWORD wAttr1, DWORD wAttr2)
{
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);
	SetConsoleTextAttribute(hStdout, wAttr1);
	SetConsoleTextAttribute(hStdout, wAttr2);
	for (int i = 0; i < list.size(); i++) {
		SetConsoleCursorPosition(hStdout, c[i+1]);
		cout << list.at(i);
	}
}

void Combo::eraseLines(int size, HANDLE hStdout)
{
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);
	for (int i = 0; i < size; i++) {
		SetConsoleCursorPosition(hStdout, c[i+1]);
		cout << "                         ";
	}
}

void Combo::changeTextColorDown(int i, HANDLE hStdout, DWORD wAttr1, DWORD wAttr2, DWORD wAttr3, DWORD wAttr4)
{
	if (i == list.size()) {
		SetConsoleTextAttribute(hStdout, wAttr3);
		SetConsoleTextAttribute(hStdout, wAttr4);
		SetConsoleCursorPosition(hStdout, c[i]);
		cout << list.at(i-1);
		SetConsoleTextAttribute(hStdout, wAttr1);
		SetConsoleTextAttribute(hStdout, wAttr2);
	}
	else {
		SetConsoleTextAttribute(hStdout, wAttr3);
		SetConsoleTextAttribute(hStdout, wAttr4);
		SetConsoleCursorPosition(hStdout, c[i+1]);
		cout << list.at(i);
		SetConsoleTextAttribute(hStdout, wAttr1);
		SetConsoleTextAttribute(hStdout, wAttr2);
	}
}

void Combo::changeTextColorUp(int i, HANDLE hStdout, DWORD wAttr1, DWORD wAttr2, DWORD wAttr3, DWORD wAttr4)
{
	printLines(hStdout, wAttr1, wAttr2);
	SetConsoleTextAttribute(hStdout, wAttr3);
	SetConsoleTextAttribute(hStdout, wAttr4);
	if (i == 0) {
		SetConsoleCursorPosition(hStdout, c[i + 1]);
		cout << list.at(i);
	}
	else {
		SetConsoleCursorPosition(hStdout, c[i]);
		cout << list.at(i - 1);
	}
	SetConsoleTextAttribute(hStdout, wAttr1);
	SetConsoleTextAttribute(hStdout, wAttr2);
}