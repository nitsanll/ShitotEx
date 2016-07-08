#include "Combobox.h"
#include "Button.h"

Combo::Combo(int width, vector<string> entries) :Panel(entries.size() + 1, width), _cursorPosition(0), label(width - 1, deafult), button(1), inner(entries.size(), width)
{
	list = entries;
	deafult = "          ";
	button.SetText("v");
	button.AddListener(*this);
	AddiControl(label, 0, 0);
	AddiControl(button, width - 1, 0);
	AddiControl(inner, 0, 1);
	for (size_t i = 0; i < entries.size(); ++i)
	{
		auto *b = new Button(width);
		b->SetText(entries[i]);
		b->AddListener(*this);
		inner.AddiControl(*b, 0, i);
		buttons.push_back(b);
	}
	inner.setLayer(getLayer() + 1);
	inner.hide();
}

void Combo::setLayer(size_t newLayer)
{ 
	Panel::setLayer(newLayer);
	inner.setLayer(newLayer + 1);
}

void Combo::MousePressed(Button &b, int x, int y, bool isLeft)
{
	if(&b == &button)
		inner.setVisibility(!inner.getVisibility());
	else {
		vector<iControl*> tmp;
		inner.getAllControls(tmp);
		for (auto c : tmp)
		{
			if (c == &b)
			{
				label.SetText(b.GetText());
				inner.hide();
			}
		}
	}
}

vector<string> Combo::getList()
{
	return list;
}

size_t Combo::GetSelectedIndex()
{
	for (int i = 0; i < list.size(); i++)
	{
		if (deafult.compare(list.at(i)) == 0) {
			return i;
		}
	}
}

void Combo::SetSelectedIndex(size_t index)
{
	deafult = list.at(index);
}

// function that changes the line's color while traversing the list  
static void switchColors(iControl &c)
{
	Color fg = c.getForeground();
	Color bg = c.getBackground();
	c.setForeground(bg);
	c.setBackground(fg);
}

void Combo::KeyEventProc(KEY_EVENT_RECORD ker, HANDLE hStdout)
{
	if (ker.bKeyDown)
	{
		switch (ker.wVirtualKeyCode)
		{
		case VK_UP:
			if (_cursorPosition > 1)
			{
				_cursorPosition = _cursorPosition - 1;
				switchColors(*buttons[_cursorPosition]);
				switchColors(*buttons[_cursorPosition - 1]);
			}
			break;
		case VK_DOWN:
			if (_cursorPosition < list.size())
			{
				if (_cursorPosition == 0) {
					_cursorPosition = _cursorPosition + 1;
					switchColors(*buttons[_cursorPosition-1]);
				}
				else {
					_cursorPosition = _cursorPosition + 1;
					switchColors(*buttons[_cursorPosition - 2]);
					switchColors(*buttons[_cursorPosition-1]);
				}
			}
			break;
		case VK_RETURN:
		{
			selectLine();
			break;
		}
		case VK_SPACE:
		{
			selectLine();
			break;
		}
		default:
			break;
		}
	}
}

void Combo::selectLine()
{
	SetSelectedIndex(_cursorPosition - 1);
	label.SetText(deafult);
	inner.hide();
}

void Combo::setBackground(Color newColor)
{
	button.setBackground(newColor);
	label.setBackground(newColor);
	for (auto b : buttons) {
		b->setBackground(newColor);
	}

}

void Combo::setForeground(Color newColor)
{
	button.setForeground(newColor);
	label.setForeground(newColor);
	for (auto b : buttons) {
		b->setForeground(newColor);
	}
}

Combo::~Combo()
{
	delete this;
}

