#include "CheckList.h"

CheckList::CheckList(short height, short width, vector <string> options) : iControl({ position.X, position.Y }, { width + 3, height }), _cursorPosition(0)
{
	list = options;
	for (auto &s : list)
		s = "[ ]" + s; //add barckets to the begining of the string
}

//draw checklist
void CheckList::draw(Graphics &g, int left, int top, int layer) {
	if (layer == 0)
	{
		iControl::draw(g, left, top, layer);
		for (int i = 0; i < list.size(); i++)
		{
			g.setForeground(Color::White);
			g.write(getCol(), getLine() + i, list[i]);
		}
		if (iControl::getFocus() == this)
		{
			vector<size_t> temp = GetSelectedIndices();
			for (int i = 0; i < list.size(); i++)
			{
				if (i == _cursorPosition) //indicator cursor
				{
					g.setBackground(Color::White);
					g.setForeground(Color::Black);
					g.write(getCol(), getLine() + _cursorPosition, list[i]);
				}
				for (int j = 0; j < temp.size(); j++)
				{
					if (i == temp[j]) //indicator selected
					{
						g.setBackground(Color::Black);
						g.setForeground(Color::White);
						g.write(getCol(), getLine() + i, list[i]);
						g.write(getCol() + 1, getLine() + i, "x");
					}
				}

				for (int j = 0; j < temp.size(); j++) //diffrent color for selected+cursor
				{
					if (i == _cursorPosition && i == temp[j])
					{
						g.setBackground(Color::White);
						g.setForeground(Color::Black);
						g.write(getCol(), getLine() + i, list[i]);
						g.write(getCol() + 1, getLine() + i, "x");
					}
				}
			}
			g.setBackground(Color::Black);
			g.setForeground(Color::White);
			g.moveTo(getCol() + 1, getLine() + _cursorPosition);
		}
	}
}
//get the indexes that was selected 
vector<size_t> CheckList::GetSelectedIndices()
{
	vector<size_t> posChecked;
	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < choice.size(); j++)
		{
			if (list[i] == choice[j])
			{
				posChecked.push_back(i);
			}
		}
	}
	return posChecked;
}
//go up with keybord
void CheckList::upFunction()
{
	if (_cursorPosition > 0) _cursorPosition = _cursorPosition - 1;
}
//go down with keybord
void CheckList::downFunction()
{
	if (_cursorPosition < list.size() - 1) _cursorPosition = _cursorPosition + 1;
}
//tab with keybord
void CheckList::tabFunction()
{
	if (_cursorPosition < +list.size() - 1) _cursorPosition = _cursorPosition + 1;
}
//select with mouse
void CheckList::chooseMouseList(int left, int top)
{
	int found = 0;
	if (top >= 0 && top <= getHeight() && left == 1)
	{
		_cursorPosition = top;
		for (int k = 0; k < choice.size(); k++)
		{
			if (choice[k] == list[_cursorPosition])
			{
				DeselectIndex(k);
				found = 1;
			}
		}
		if (found == 0)
			SelectIndex(_cursorPosition);
	}
}
//choose with keybord
void CheckList::returnFunctionList()
{
	int found = 0;
	for (int k = 0; k < choice.size(); k++)
	{
		if (choice[k] == list[_cursorPosition])
		{
			DeselectIndex(k);
			found = 1;
		}
	}
	if (found == 0)
		SelectIndex(_cursorPosition);
}
//insert selected index to choice
void CheckList::SelectIndex(size_t index)
{
	choice.push_back(list[index]);
}
//deselect selected inex from choice
void CheckList::DeselectIndex(size_t index)
{
	choice.erase(choice.begin() + index);
}
//when keybord was pressed
VOID CheckList::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput)
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
			returnFunctionList();
			break;
		default:
			break;
		}
	}
}
//when mouse was clicked
void CheckList::MouseClicked(int left, int top, bool isLeft)
{
	chooseMouseList(left, top);
	iControl::setFocus(*this); //move focus
}