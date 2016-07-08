#include "EventEngine.h"
#include <typeinfo>
#include<iostream>

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void EventEngine::run(iControl &c)
{
	INPUT_RECORD irInBuf[128];
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	for (bool redraw = true;;)
	{
		if (redraw)
		{
			_graphics.clearScreen();
			_graphics.setCursorVisibility(false);
			for (size_t p = 0; p < 5; ++p)
				c.draw(_graphics, 0, 0, p);
			redraw = false;
		}

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			auto f = iControl::getFocus();
			if (f != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto eve = record.Event.KeyEvent;
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				if (code == VK_TAB)
				{
					if (f->innerTab() == true && f->getCurrnetPos() < f->getHeight() - 1)
					{
						f->KeyEventProc(eve, hStdout);
					}
					else
					{
						moveFocus(c, f);
					}
				}
				else
					f->KeyEventProc(eve, hStdout);
				redraw = true;
			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto eve = record.Event.MouseEvent;
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X - c.getCol();
			auto y = coord.Y - c.getLine();

			vector<iControl*> controls;
			c.getAllControls(controls);

			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				c.MouseClicked(coord.X, coord.Y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
				redraw = true;
			}
		}

		break;
		default:
			break;
		}
	}
}
EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

void EventEngine::moveFocus(iControl &main, iControl *focused)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<iControl*> controls;
	main.getAllControls(controls);
	auto it = find(controls.begin(), controls.end(), focused); //it points to a control
	do
		if (++it == controls.end())
			it = controls.begin();
	while (!(*it)->canGetFocus()); //stop loop when control can get focus

	iControl::setFocus(**it); //set control in focus
	SetConsoleCursorPosition(hStdout, { (*it)->getCol(), (*it)->getLine() });
}
