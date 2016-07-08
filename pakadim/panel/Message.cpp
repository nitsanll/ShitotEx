#include "Message.h"

Messagebox::Messagebox(int height, int width) :Panel(height, width), title(width, "title"), text(width, "text here"), ok(6), cancel(6)
{
	value = "";
	ok.SetText("ok");
	cancel.SetText("cancel");
	ok.AddListener(*this);
	cancel.AddListener(*this);
	AddiControl(title, 0, 0);
	AddiControl(text, 0, 2);
	AddiControl(ok, 0, 3);
	AddiControl(cancel, 3, 3);
}

void Messagebox::SetText(string _text)
{
	text.SetText(_text);
}

void Messagebox::SetTitle(string _title)
{
	title.SetText(_title);
}

//whem mouse pressed the value is updated according to the user's choice, and than hide the message box
void Messagebox::MousePressed(Button &b, int x, int y, bool isLeft)
{
	if (&b == &ok)
	{
		value = ok.GetText();
		(*this).hide();
	}
	else if (&b == &cancel)
	{
		value = cancel.GetText();
		(*this).hide();
	}
}

void Messagebox::setBackground(Color newColor)
{
	title.setBackground(newColor);
	text.setBackground(newColor);
	ok.setBackground(newColor);
	cancel.setBackground(newColor);
}

void Messagebox::setForeground(Color newColor)
{
	title.setForeground(newColor);
	text.setForeground(newColor);
	ok.setForeground(newColor);
	cancel.setForeground(newColor);
}