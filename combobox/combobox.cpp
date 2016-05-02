#include "Combobox.h"

Combo::Combo() :iControl({ 7, 7 }, { 100, 100 })
{
	list = { "1990", "1991", "1992" };
	deafult = "   ";
	draw();
}

vector<string> Combo::getList()
{
	return list;
}

string Combo::getDeafult()
{
	return deafult;
}

void Combo::setDeafult(string str)
{
	deafult = str;
}

void Combo::draw()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c[] = { { 7, 7 },{ 7,8 },{ 7,9 },{ 7,10 } };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);

	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hStdout, wAttr1);

	SetConsoleCursorPosition(hStdout, c[0]);

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);

	cout << getDeafult() + " " + 'V' << endl;

	SetConsoleCursorPosition(hStdout, c[0]);
}

void Combo::MouseEventProc(MOUSE_EVENT_RECORD mer, HANDLE hStdout, int line)
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
	COORD c[] = { { 7, 8 },{ 7,9 },{ 7,10 } };
	string erase = "          ";
	if (mer.dwEventFlags == 0)
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			vector<string> str = list;
			if (mer.dwMousePosition.Y == line && mer.dwMousePosition.X >= 7 && mer.dwMousePosition.X <= 12)
			{
				printLines(hStdout, wAttr1, wAttr2);
			}

			for (int i = 0, j = 1; i < str.size(); i++, j++) {
				if (mer.dwMousePosition.Y == line + j && mer.dwMousePosition.X >= 7 && mer.dwMousePosition.X <= 12)
				{
					setDeafult(str.at(i));
					SetConsoleCursorPosition(hStdout, { 7,7 });
					SetConsoleTextAttribute(hStdout, wAttr1);
					cout << deafult + " " + 'V' << endl;
					eraseLines(erase, str.size(), hStdout);
					SetConsoleCursorPosition(hStdout, { 7,7 });
				}
			}
		}
	}
}

void Combo::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hStdout, int line)
{
	COORD c[] = { { 7, 8 },{ 7,9 },{ 7,10 } };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	COORD coord = cbi.dwCursorPosition;
	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	DWORD wAttr2 = cbi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	DWORD wAttr3 = cbi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	DWORD wAttr4 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	string erase = "          ";

	const WORD up = VK_UP;
	const WORD down = VK_DOWN;
	const WORD enter = VK_RETURN;
	if (ker.bKeyDown) {
		if (ker.wVirtualKeyCode == up)
		{
			GetConsoleScreenBufferInfo(hStdout, &cbi);
			coord = cbi.dwCursorPosition;
			if (coord.Y == 10) {
				changeTextColorUp(2, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
			}
			if (coord.Y == 9) {
				changeTextColorUp(1, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
			}
		}

		if (ker.wVirtualKeyCode == down)
		{
			if (coord.Y == line)
			{
				printLines(hStdout, wAttr1, wAttr2);
				changeTextColorDown(0, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
			}

			else
			{
				GetConsoleScreenBufferInfo(hStdout, &cbi);
				coord = cbi.dwCursorPosition;
				printLines(hStdout, wAttr1, wAttr2);
				if (coord.Y == line + 1) changeTextColorDown(1, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
				if (coord.Y == line + 2) changeTextColorDown(2, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
				if (coord.Y == line + 3) changeTextColorDown(3, hStdout, wAttr1, wAttr2, wAttr3, wAttr4);
			}
		}

		if (ker.wVirtualKeyCode == enter)
		{
			GetConsoleScreenBufferInfo(hStdout, &cbi);
			coord = cbi.dwCursorPosition;
			int i = coord.Y;
			setDeafult(list.at(i - 8));
			SetConsoleCursorPosition(hStdout, { 7,7 });
			SetConsoleTextAttribute(hStdout, wAttr1);
			cout << deafult + " " + 'V' << endl;
			eraseLines(erase, list.size(), hStdout);
			SetConsoleCursorPosition(hStdout, { 7,7 });
		}
	}
}

void Combo::printLines(HANDLE hStdout, DWORD wAttr1, DWORD wAttr2)
{
	COORD c[] = { { 7, 8 },{ 7,9 },{ 7,10 } };
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);
	SetConsoleTextAttribute(hStdout, wAttr1);
	SetConsoleTextAttribute(hStdout, wAttr2);
	for (int i = 0; i < list.size(); i++) {
		SetConsoleCursorPosition(hStdout, c[i]);
		cout << list.at(i);
	}
}

void Combo::eraseLines(string tmp, int size, HANDLE hStdout)
{
	COORD c1[] = { { 7,8 },{ 7,9 },{ 7,10 } };
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(hStdout, &cci);

	for (int i = 0; i < size; i++) {
		SetConsoleCursorPosition(hStdout, c1[i]);
		cout << tmp;
	}
}

void Combo::changeTextColorDown(int i, HANDLE hStdout, DWORD wAttr1, DWORD wAttr2, DWORD wAttr3, DWORD wAttr4)
{
	COORD c[] = { { 7, 8 },{ 7,9 },{ 7,10 } };
	if (i == 3) {
		SetConsoleCursorPosition(hStdout, c[i - 1]);
		SetConsoleTextAttribute(hStdout, wAttr3);
		SetConsoleTextAttribute(hStdout, wAttr4);
		cout << list.at(i - 1);
	}
	else {
		SetConsoleTextAttribute(hStdout, wAttr3);
		SetConsoleTextAttribute(hStdout, wAttr4);
		SetConsoleCursorPosition(hStdout, c[i]);
		cout << list.at(i);
	}
	SetConsoleTextAttribute(hStdout, wAttr1);
	SetConsoleTextAttribute(hStdout, wAttr2);
}

void Combo::changeTextColorUp(int i, HANDLE hStdout, DWORD wAttr1, DWORD wAttr2, DWORD wAttr3, DWORD wAttr4)
{
	COORD c[] = { { 7, 8 },{ 7,9 },{ 7,10 } };
	printLines(hStdout, wAttr1, wAttr2);
	SetConsoleTextAttribute(hStdout, wAttr3);
	SetConsoleTextAttribute(hStdout, wAttr4);
	SetConsoleCursorPosition(hStdout, c[i - 1]);
	cout << list.at(i - 1);
	SetConsoleTextAttribute(hStdout, wAttr1);
	SetConsoleTextAttribute(hStdout, wAttr2);
}

Combo::~Combo() {};