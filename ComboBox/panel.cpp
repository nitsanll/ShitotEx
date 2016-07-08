#include "panel.h"
#include <typeinfo>

Panel::Panel(short _width, short _height) : iControl({ 0,0 }, { _width,_height })
{
	height = _height;
	width = _width;
	//currentPos = position;
}

Panel::~Panel() {};
/*
void Panel::AddiControl(iControl &icontrol)
{
if (icontrol.getHeight() < height && icontrol.getWidth() < width) {
controls.push_back(&icontrol);
icontrol.setPosition(currentPos);
currentPos.Y += icontrol.getHeight();
currentPos.Y += 2;
const type_info &t = typeid(icontrol);
//cout << t.name() << endl;
//string str = t.name();
if (strcmp("class Panel", t.name())) {
//check panel position and change controls in it.
//addPanel();
}
}
else { cout << "cannot add this control to panel! size overflow"; }
}
*/

void Panel::AddiControl(iControl &icontrol, short left, short top)
{
	if (icontrol.getHeight() <= height && icontrol.getWidth() <= width) {
		icontrol.setPosition({ left, top });
		//cout << icontrol.getLine() << icontrol.getCol() << endl;
		controls.push_back(&icontrol);
	}
	else { cout << "cannot add this control to panel! size overflow"; }
}


/*void Panel::addPanel(Panel& panel)
{
vector<iControl *>::iterator it;
panel.currentPos = panel.position;
for (it = panel.controls.begin(); it != panel.controls.end(); ++it) {
(*it)->setPosition(currentPos);
panel.currentPos.Y += (*it)->getHeight();
panel.currentPos.Y += 2;
}
}*/

void Panel::draw()
{
	vector<iControl *>::iterator it;
	for (it = controls.begin(); it != controls.end(); ++it) {
		(*it)->draw();
	}
}

/*int Panel::getCurrentLine()
{
return currentPos.X;
}*/