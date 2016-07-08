#include "panel.h"
#include <typeinfo>
Panel::Panel(short _height, short _width) : iControl({ 0, 0 }, { _width, _height })
{
}
Panel::~Panel() {};

void Panel::AddiControl(iControl &icontrol, short left, short top)
{
	if (icontrol.getHeight() <= getHeight() && icontrol.getWidth() <= getWidth()) {
		controls.push_back(&icontrol);
		icontrol.setPosition({ left, top });
	}
	else { 
		cout << "cannot add this control to panel! size overflow"; 
	}
}
void Panel::draw(Graphics &g, int left, int top, int layer)
{
	if (!visibility)
		return;
	
	if (layer == getLayer()) {
		iControl::draw(g, left, top, layer);
		/*for (int i = 0; i < getWidth(); i++) {
			/*for (int j = 0; j < getHeight(); j++) {
				g.write(i + left + getCol(),j + top + getLine()," ");
			}
		}*/
	}
	
	for (auto c : controls) {
		c->draw(g, left + getCol(), top + getLine(), layer);
	}
}

void Panel::setLayer(size_t newLayer)
{
	iControl::setLayer(newLayer);
	for (auto c : controls)
		c->setLayer(newLayer);
}

void Panel::MouseClicked(int left, int top, bool isLeft)
{
	for (auto c : controls)
	{
		int dx = left - c->getCol();
		int dy = top - c->getLine();
		if (dx >= 0 && dy >= 0 && dx < c->getWidth() && dy < c->getHeight())
			c->MouseClicked(dx, dy, isLeft);
			iControl::setFocus(*this); //move focus
	}
}