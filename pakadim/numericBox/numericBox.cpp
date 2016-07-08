#include "numericBox.h"

NumericBox::NumericBox(int _width, int _min, int _max):Panel(1,_width)
{
	min = _min;
	max = _max;
	value = min;
	Label l((_width - 2), to_string(min));
	Button b1(1);
	Button b2(1);
	b1.SetText("-");
	b2.SetText("+");
	label = l;
	button1 = b1;
	button2 = b2;
	//draw();
}

int NumericBox::GetValue()
{
	return value;
}

bool NumericBox::SetValue(int _value)
{
	if (_value < min) {
		value++;
		return false;
	}
	else if (_value > max) {
		value--;
		return false;
	}
	else {
		value = _value;
		return true;
	}
}

void NumericBox::draw() 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	DWORD wAttr1 = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hStdout, wAttr1);

	SetConsoleCursorPosition(hStdout, position);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	
	AddiControl(button1, position.X, position.Y);
	AddiControl(label, (position.X + 1), position.Y);
	AddiControl(button2, position.X + (width - 1), position.Y);
	controls.at(0)->draw();
	controls.at(1)->draw();
	controls.at(2)->draw();
}

void NumericBox::MouseEventProc(MOUSE_EVENT_RECORD mer, HANDLE hStdout)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(hStdout, &cbi);
	if (mer.dwEventFlags == 0)
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (mer.dwMousePosition.Y == getLine() && mer.dwMousePosition.X == position.X)
			{
				SetValue(--value);
				label.SetText(to_string(value));
				label.draw();
			}
			if (mer.dwMousePosition.Y == getLine() && mer.dwMousePosition.X == position.X + (size.X - 1))
			{
				SetValue(++value);
				label.SetText(to_string(value));
				label.draw();
			}	
		}
	}
}