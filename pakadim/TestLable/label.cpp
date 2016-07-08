#include "Label.h"
#include "TextBox.h"

Label::Label(int widthNew, string val) :TextBox(widthNew)
{
	stringInput = val;
	SetText(val);
}
