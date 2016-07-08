#include "checkList.h"

//using namespace std;

CheckList::CheckList() : iControl({ 7, 7 }, { 100, 100 })
{
	draw();
}
void CheckList::draw(void)
{
	vector<string> myList = { "[ ]hello", "[ ] hi", "[ ]love" };
	list = myList;

	short startLine = 7;
	short newLineY = startLine;

	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);

	for (int i = 0; i < myList.size(); i++)
	{
		c = { startLine, newLineY++ };
		SetConsoleCursorPosition(h, c);
		cout << myList[i] << endl;
	}


	CONSOLE_CURSOR_INFO cci = { 10, TRUE };
	SetConsoleCursorInfo(h, &cci);

	c = { startLine + 1, startLine };
	SetConsoleCursorPosition(h, c);
}
VOID CheckList::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput, int line)
{

	COORD newCoord;
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi);


	short newLineY = line;
	for (int i = 0; i < list.size(); i++)
	{
		int wasChoosen = 0;
		newCoord = { line, newLineY };
		SetConsoleCursorPosition(hConsoleOutput, newCoord);

		for (int j = 0; j < choice.size(); j++)
		{
			if (list[i] == choice[j])
				wasChoosen = 1;
		}

		if (wasChoosen == 1)
		{

			DWORD wAttr = cbsi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			SetConsoleTextAttribute(hConsoleOutput, wAttr);
			DWORD wAttr2 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			SetConsoleTextAttribute(hConsoleOutput, wAttr2);

			cout << list[i];
			newCoord = { line + 1, newLineY };
			SetConsoleCursorPosition(hConsoleOutput, newCoord);
			cout << "x";

			wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			SetConsoleTextAttribute(hConsoleOutput, wAttr);
			wAttr2 = cbsi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			SetConsoleTextAttribute(hConsoleOutput, wAttr2);
			newLineY++;
		}

		else if (cbsi.dwCursorPosition.Y == newLineY)
		{
			DWORD wAttr = cbsi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			SetConsoleTextAttribute(hConsoleOutput, wAttr);
			DWORD wAttr2 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			SetConsoleTextAttribute(hConsoleOutput, wAttr2);
			cout << list[i];

			wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			SetConsoleTextAttribute(hConsoleOutput, wAttr);
			wAttr2 = cbsi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			SetConsoleTextAttribute(hConsoleOutput, wAttr2);
			newLineY++;
		}

		else
		{
			newCoord = { line, newLineY };
			SetConsoleCursorPosition(hConsoleOutput, newCoord);
			cout << list[i];
			newLineY++;
		}

		newCoord = { line + 1, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsoleOutput, newCoord);


	}


	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode)
		{

		case VK_UP:
		{
			if (cbsi.dwCursorPosition.Y > line)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y - 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
			else if (cbsi.dwCursorPosition.Y == line)
			{
				newCoord = { cbsi.dwCursorPosition.X, line + 2 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
		}
		break;
		case VK_NUMPAD8:
		{
			if (cbsi.dwCursorPosition.Y > line)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y - 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
			else if (cbsi.dwCursorPosition.Y == line)
			{
				newCoord = { cbsi.dwCursorPosition.X, line + 2 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
		}
		break;
		case VK_DOWN:
		{
			int num;
			if (cbsi.dwCursorPosition.Y < line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y + 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
			else if (cbsi.dwCursorPosition.Y == line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, line };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
		}
		break;
		case VK_NUMPAD2:
		{
			if (cbsi.dwCursorPosition.Y < line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y + 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
			else if (cbsi.dwCursorPosition.Y == line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, line };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
		}
		break;
		case VK_TAB:
		{
			int num;
			if (cbsi.dwCursorPosition.Y < line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y + 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
			else if (cbsi.dwCursorPosition.Y == line + list.size() - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X, line };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);

			}
			break;
		}
		case VK_RETURN:
		{

			COORD newCoord;
			int newLineY = line;
			int found = 0;

			for (int i = 0, j = line; i < list.size(); i++, j++)
			{
				if (cbsi.dwCursorPosition.Y == j && cbsi.dwCursorPosition.X >= line && cbsi.dwCursorPosition.X <= line + 2)
				{
					for (int k = 0; k < choice.size(); k++)
					{
						if (choice[k] == list[i])
						{
							eraseChoice(k);
							found = 1;
						}
					}
					if (found == 0)
						SetChoice(list[i]);

				}
			}

			break;
		}
		default:
			break;
		}
	}



}

VOID CheckList::MouseEventProc(MOUSE_EVENT_RECORD mer, HANDLE hStdin, int line)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");
	int start = 7;


	if (mer.dwButtonState)
	{
		switch (mer.dwEventFlags)
		{
		case MOUSE_MOVED:
			break;
		case 0:
		{
			if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD newCoord;
				CONSOLE_SCREEN_BUFFER_INFO cbsi;
				GetConsoleScreenBufferInfo(hStdin, &cbsi);
				int newLineY = line;
				int found = 0;

				for (int i = 0, j = line; i < list.size(); i++, j++)
				{
					if (mer.dwMousePosition.Y == j && mer.dwMousePosition.X >= start && mer.dwMousePosition.X <= start + 2)
					{
						for (int k = 0; k < choice.size(); k++)
						{
							if (choice[k] == list[i])
							{
								eraseChoice(k);
								found = 1;
							}
						}
						if (found == 0)
							SetChoice(list[i]);

					}
				}
			}


			else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD newCoord;
				CONSOLE_SCREEN_BUFFER_INFO cbsi;
				GetConsoleScreenBufferInfo(hStdin, &cbsi);
				int newLineY = line;
				int found = 0;

				for (int i = 0, j = line; i < list.size(); i++, j++)
				{
					if (mer.dwMousePosition.Y == j && mer.dwMousePosition.X >= start && mer.dwMousePosition.X <= start + 2)
					{
						for (int k = 0; k < choice.size(); k++)
						{
							if (choice[k] == list[i])
							{
								eraseChoice(k);
								found = 1;
							}
						}
						if (found == 0)
							SetChoice(list[i]);
					}
				}
			}
		case DOUBLE_CLICK:
			break;
		case MOUSE_HWHEELED:
			break;
		case MOUSE_WHEELED:
			break;
		default:
			break;
		}
		}
	}
	COORD newCoord;
	int newLineY = line;


	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(hStdin, &cbsi);

	//	int rem = mer.dwMousePosition.Y;

	for (int i = 0; i < list.size(); i++)
	{
		int found = 0;
		newCoord = { line, newLineY };
		SetConsoleCursorPosition(hStdin, newCoord);


		if (mer.dwMousePosition.Y == newLineY)
		{
			for (int j = 0; j < choice.size(); j++)
			{
				if (list[i] == choice[j])
				{
					found = 1;
				}
			}
			if (found != 1)
			{
				DWORD wAttr = cbsi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				SetConsoleTextAttribute(hStdin, wAttr);
				DWORD wAttr2 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
				SetConsoleTextAttribute(hStdin, wAttr2);
				cout << list[i];

				wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				SetConsoleTextAttribute(hStdin, wAttr);
				wAttr2 = cbsi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				SetConsoleTextAttribute(hStdin, wAttr2);
				newLineY++;
			}
		}
		else
		{
			newCoord = { line, newLineY };
			SetConsoleCursorPosition(hStdin, newCoord);
			for (int j = 0; j < choice.size(); j++)
			{
				if (list[i] == choice[j])
				{
					found = 1;
				}

			}
			if (found != 1)
			{
				cout << list[i];
				newLineY++;
			}
		}
		if (found == 1)
		{
			newCoord = { line, newLineY };
			SetConsoleCursorPosition(hStdin, newCoord);
			DWORD wAttr = cbsi.wAttributes &  ~(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			SetConsoleTextAttribute(hStdin, wAttr);
			DWORD wAttr2 = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			SetConsoleTextAttribute(hStdin, wAttr2);
			SetConsoleCursorPosition(hStdin, newCoord);
			cout << list[i];
			newCoord = { line + 1, newLineY };
			SetConsoleCursorPosition(hStdin, newCoord);
			cout << "x";
			wAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			SetConsoleTextAttribute(hStdin, wAttr);
			wAttr2 = cbsi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			SetConsoleTextAttribute(hStdin, wAttr2);
			newLineY++;
		}

		newCoord = { line + 1, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hStdin, newCoord);

	}

}
CheckList::~CheckList()
{

}

void CheckList::SetList(vector<string> newlist)
{
	list = newlist;
}
vector<string> CheckList::GetList()
{
	return list;
}

void CheckList::SetChoice(string select)
{
	choice.push_back(select);
}
vector<string> CheckList::GetChoice()
{
	return choice;
}
void CheckList::eraseChoice(int num)
{
	choice.erase(choice.begin() + num);
}