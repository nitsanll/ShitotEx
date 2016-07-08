#include "radioList.h"

using namespace std;

RadioList::RadioList(short height, short width, vector <string> options) : CheckList(height, width, options)
{

}

VOID RadioList::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput)
{
	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode)
		{
		case VK_UP:
			upFunction();
			break;
		case VK_DOWN:
			downFunction();
			break;
		case VK_TAB:
			tabFunction();
			break;
		case VK_SPACE:
		case VK_RETURN:
			returnFunctionRadio();
			break;
		default:
			break;
		}
	}
}

//select with mouse
void RadioList::chooseMouseRadio(int X, int Y)
{
	if (Y >= 0 && Y <= 0 + getHeight() && X == 1)
	{
		_cursorPosition = Y;
		for (int k = 0; k < choice.size(); k++)
		{
			if (choice[k] != list[_cursorPosition])
			{
				DeselectIndex(k);
				SelectIndex(_cursorPosition);
			}
		}
		if (choice.size() == 0)
		{
			SelectIndex(_cursorPosition);
		}
	}
}

//select with keybord
void RadioList::returnFunctionRadio()
{
	for (int k = 0; k < choice.size(); k++)
	{
		if (choice[k] != list[_cursorPosition])
		{
			DeselectIndex(k);
			SelectIndex(_cursorPosition);
		}
	}
	if (choice.size() == 0)
		SelectIndex(_cursorPosition);
}

//when mouse was clicked
void RadioList::MouseClicked(int left, int top, bool isLeft)
{
	chooseMouseRadio(left, top);
	iControl::setFocus(*this); //move focus
}