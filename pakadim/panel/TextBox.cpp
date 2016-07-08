#include "TextBox.h"
#include "Graphics.h"

TextBox::TextBox(short widthNew) :iControl({ position.X, position.Y }, { widthNew, 1 }), _cursorPosition(0)
{
}
void TextBox::draw(Graphics &g, int left, int top, int layer)
{
	if (!visibility)
		return;
	if (layer == 0)
	{
		iControl::draw(g, left, top, layer);
		g.write(left + getCol(), top + getLine(), stringInput);
	}
	else if (layer == 1)
	{
		if (iControl::getFocus() == this)
		{
			g.setCursorVisibility(true);
			g.moveTo(left + getCol() + _cursorPosition, top + getLine());
		}
	}
}
//function when key was pressed
void TextBox::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hConsoleOutput)
{
	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode) {
		case VK_LEFT:
			_cursorPosition = max(_cursorPosition - 1, 0);
			break;
		case VK_RIGHT:
			_cursorPosition = min(_cursorPosition + 1, stringInput.size());
			break;
		case VK_BACK:
			if (_cursorPosition > 0)
				stringInput.erase(--_cursorPosition, 1);
			break;
		case VK_DELETE:
			if (_cursorPosition < stringInput.size())
				stringInput.erase(_cursorPosition, 1);
			break;
		default:
			if (ker.wVirtualKeyCode >= 0x30 && ker.wVirtualKeyCode <= 0x5A && stringInput.size() < getWidth())
			{
				stringInput.insert(stringInput.begin() + _cursorPosition, ker.uChar.AsciiChar);
				_cursorPosition++;
			}
			break;
		}
	}
}
void TextBox::MouseClicked(int left, int top, bool isLeft)
{
	_cursorPosition = left;
	iControl::setFocus(*this); //move focus

}
string TextBox::GetText()
{
	return stringInput;
}
void TextBox::SetText(string str) {
	stringInput = str;
	_cursorPosition = str.size();
}