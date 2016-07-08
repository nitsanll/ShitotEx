#include "TextBox.h"

TextBox::TextBox(short widthNew) :iControl({ 7, 7 }, { widthNew, 1 })
{
	//position = { 7, 7 };
	//size.X = size.XNew;
	//draw();
}

void TextBox::draw()
{
	int max = position.X + size.X;
	COORD c = position;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
	cout << stringInput;
}

void TextBox::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput)
{

	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	COORD newCoord;
	GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi);
	short newLine = position.Y;
	short maxBox = position.X + size.X;


	CONSOLE_CURSOR_INFO cci = { 10, TRUE };
	SetConsoleCursorInfo(hConsoleOutput, &cci);


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
		case VK_RIGHT:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox - 1 && cbsi.dwCursorPosition.X < newLine + stringInput.length())
			{
				newCoord = { cbsi.dwCursorPosition.X + 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		case VK_NUMPAD6:
		{
			if (cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox - 1 && cbsi.dwCursorPosition.X < newLine + stringInput.length())
			{
				newCoord = { cbsi.dwCursorPosition.X + 1, cbsi.dwCursorPosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
			}
		}
		break;
		default:
		{
			string checkLength = GetText();


			if (ker.bKeyDown)
			{
				int wasEraseDel = 0;
				int okValue = 0;
				int wasEraseBackSpace = 0;

				if (ker.wVirtualKeyCode == VK_BACK)
				{
					string str = GetText();
					EraseBackSpace(str, cbsi.dwCursorPosition.X - newLine);
					wasEraseBackSpace = 1;
				}

				else if (ker.wVirtualKeyCode == VK_DELETE)
				{
					string str = GetText();
					EraseDel(str, cbsi.dwCursorPosition.X - newLine);
					wasEraseDel = 1;
				}

				else
				{
					if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x5A && cbsi.dwCursorPosition.Y == newLine && cbsi.dwCursorPosition.X < maxBox)
					{
						string str(1, ker.uChar.AsciiChar);
						SetChar(str);
						okValue = 1;
					}


				}
				short saveXPosition = cbsi.dwCursorPosition.X;
				short saveYPosition = cbsi.dwCursorPosition.Y;

				newCoord = { newLine, newLine };
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
				if (wasEraseDel == 1 || wasEraseBackSpace == 1)
				{
					for (int i = 0; i < size.X; i++)
						cout << " ";
				}
				SetConsoleCursorPosition(hConsoleOutput, newCoord);
				string temp = GetText();
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
				else if (wasEraseBackSpace == 1 && cbsi.dwCursorPosition.X >newLine)
				{
					newCoord = { saveXPosition - 1, cbsi.dwCursorPosition.Y };
					SetConsoleCursorPosition(hConsoleOutput, newCoord);
				}
				else if (wasEraseBackSpace == 1 && cbsi.dwCursorPosition.X >= newLine)
				{
					newCoord = { saveXPosition, cbsi.dwCursorPosition.Y };
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
	int start = position.Y;
	int max = position.X + size.X;

	switch (mer.dwEventFlags)
	{
	case 0:
		COORD coordMouse;

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (mer.dwMousePosition.Y == start && mer.dwMousePosition.X >= start && mer.dwMousePosition.X < max && mer.dwMousePosition.X < stringInput.length() + start + 1)
			{
				coordMouse = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
				SetConsoleCursorPosition(hConsoleOutput, coordMouse);

			}
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			if (mer.dwMousePosition.Y == start && mer.dwMousePosition.X >= start && mer.dwMousePosition.X < max && mer.dwMousePosition.X < stringInput.length() + start + 1)
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

void TextBox::SetChar(string input)
{
	if (stringInput.length() < 10)
	{
		CONSOLE_SCREEN_BUFFER_INFO cbsi;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(h, &cbsi);


		string temp(input);
		string newstring = GetText();
		newstring.insert(cbsi.dwCursorPosition.X - position.X, temp);
		stringInput.assign(newstring);
	}
}

string TextBox::GetText()
{
	return stringInput;
}


void TextBox::EraseBackSpace(string mystr, int position)
{
	if (position > 0)
	{
		mystr.erase(position - 1, 1);
		stringInput = mystr;
	}
}

void TextBox::EraseDel(string mystr, int position)
{
	mystr.erase(position, 1);
	stringInput = mystr;
}

void TextBox::SetText(string str) {
	stringInput = str;
}