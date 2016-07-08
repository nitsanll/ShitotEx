#include "iControl.h"
#include <Windows.h>
#include <iostream>
using namespace std;

iControl *iControl::focused = nullptr;

iControl::iControl(COORD p, COORD s) : visibility(true), foregroundColor(Color::White), backgroundColor(Color::Black), layer(0)
{
	position = p;
	size = s;
	setBorderDrawer(SimpleBorderFactory::instance().getNull());
}

void iControl::draw(Graphics &g, int left, int top, int layer)
{
	_borderDrawer->draw(g, getCol() + left, getLine() + top, size.X, size.Y);
	g.setBackground(backgroundColor);
	g.setForeground(foregroundColor);
}

