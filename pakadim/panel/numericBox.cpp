#include "numericBox.h"

NumericBox::NumericBox(int _width, int _min, int _max) :Panel(1, _width), label((_width - 2), to_string(_min)) ,button1(1), button2(1)
{
	min = _min;
	max = _max;
	value = min;
	button1.SetText("-");
	button2.SetText("+");
	button1.AddListener(*this);
	button2.AddListener(*this);
	AddiControl(button1, 0, 0);
	AddiControl(label, 1, 0);
	AddiControl(button2, getWidth() - 1, 0);
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

//mouse pressed changes the value and set it in the label 
void NumericBox::MousePressed(Button &b, int x, int y, bool isLeft)
{
	if (&b == &button1)
	{
		SetValue(--value);
		label.SetText(to_string(value));
	}
	if (&b == &button2)
	{
		SetValue(++value);
		label.SetText(to_string(value));
	}
}

void NumericBox::setBackground(Color newColor) 
{
	button1.setBackground(newColor);
	button2.setBackground(newColor);
	label.setBackground(newColor);

}

void NumericBox::setForeground(Color newColor)
{
	button1.setForeground(newColor);
	button2.setForeground(newColor);
	label.setForeground(newColor);
}