#include "TextBox.h"

TextBox::TextBox()
{

}
TextBox::~TextBox()
{

}
VOID TextBox::ErrorExit(LPSTR lpszMessage, HANDLE hStdin, DWORD fdwSaveOldMode)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID TextBox::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput, TextBox* t)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	COORD newCoord;
	GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi);
	int newLine = 8;
	int maxBox = 14;

	if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X == maxBox)
	{
		CONSOLE_CURSOR_INFO cci = { 10, FALSE };
		SetConsoleCursorInfo(hConsoleOutput, &cci);
	}

	else
	{
		CONSOLE_CURSOR_INFO cci = { 10, TRUE };
		SetConsoleCursorInfo(hConsoleOutput, &cci);
	}
	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode) {
		case VK_LEFT:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X >newLine)
			{
				newCoord = { cbsi.dwCursorPosition.X - 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_NUMPAD4:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X > newLine)
			{
				newCoord = { cbsi.dwCursorPosition.X - 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_UP:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox && cbsi.dwCursorPosition.Y > newLine)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y - 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_NUMPAD8:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox && cbsi.dwCursorPosition.Y > newLine)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y - 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_RIGHT:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X + 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_NUMPAD6:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox - 1)
			{
				newCoord = { cbsi.dwCursorPosition.X + 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case  VK_DOWN:
		{
			if (cbsi.dwCursorPosition.Y == newLine - 1 && cbsi.dwCursorPosition.X < maxBox)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y + 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case  VK_NUMPAD2:
		{
			if (cbsi.dwCursorPosition.Y == newLine - 1 && cbsi.dwCursorPosition.X < maxBox)
			{
				newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y + 1 };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		default:
		{
			string checkLength = t->GetstringInput();


			if (ker.bKeyDown)
			{
				int wasEraseDel = 0;
				int okValue = 0;
				int wasEraseBackSpace = 0;

				if (ker.wVirtualKeyCode == VK_BACK)
				{
					string str = t->GetstringInput();
					t->EraseBackSpace(str, cbsi.dwCursorPosition.X - newLine);
					wasEraseBackSpace = 1;
				}

				else if (ker.wVirtualKeyCode == VK_DELETE)
				{
					string str = t->GetstringInput();
					t->EraseDel(str, cbsi.dwCursorPosition.X - newLine);
					wasEraseDel = 1;
				}

				else
				{
					if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x5A && cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox)
					{
						t->SetstringInput(ker.uChar.AsciiChar, cbsi.dwCursorPosition.X - newLine);
						okValue = 1;
					}


				}
				int saveXPosition = cbsi.dwCursorPosition.X;
				int saveYPosition = cbsi.dwCursorPosition.Y;

				newCoord = { newLine, newLine };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
				if (wasEraseDel == 1 || wasEraseBackSpace == 1)
					cout << "      ";
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
				string temp = t->GetstringInput();
				cout << temp;

				if (wasEraseDel == 1)
				{
					newCoord = { cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y };
					SetConsoleCursorPosition(hConsoleOutput, newCoord);
				}
				else if (okValue == 1)
				{
					newCoord = { cbsi.dwCursorPosition.X + 1, cbsi.dwCursorPosition.Y };
					SetConsoleCursorPosition(hConsoleOutput, newCoord);
				}
				else if (wasEraseBackSpace == 1 && cbsi.dwCursorPosition.X - 1>newLine)
				{
					newCoord = { cbsi.dwCursorPosition.X - 1, cbsi.dwCursorPosition.Y };
					SetConsoleCursorPosition(hConsoleOutput, newCoord);
				}
			}
		}
		break;
		}
	}
}

VOID TextBox::MouseEventProc(MOUSE_EVENT_RECORD mer, HANDLE hConsoleOutput)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif

	int start = 8;
	int max = 14;

	switch (mer.dwEventFlags)
	{
	case 0:
		COORD coordMouse;

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (mer.dwMousePosition.Y == start && mer.dwMousePosition.X > start && mer.dwMousePosition.X < max)
			{
				coordMouse = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, coordMouse);

			}
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			if (mer.dwMousePosition.Y == start && mer.dwMousePosition.X > start && mer.dwMousePosition.X < max)
			{
				coordMouse = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, coordMouse);

			}
		}
		break;
	default:
		break;
	}
}

VOID TextBox::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
VOID TextBox::SetstringInput(char input, int position)
{
	string temp(1, input);
	string newstring = GetstringInput();
	newstring.insert(position, temp);
	stringInput = newstring;
}
string TextBox::GetstringInput()
{
	return stringInput;
}

VOID TextBox::EraseBackSpace(string mystr, int position)
{
	if (position > 0)
	{
		mystr.erase(position - 1, 1);
		stringInput = mystr;
	}
}


VOID TextBox::EraseDel(string mystr, int position)
{
	mystr.erase(position, 1);
	stringInput = mystr;
}

