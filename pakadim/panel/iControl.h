#ifndef ICONTROLH
#define ICONTROLH
#include<Windows.h>
#include <vector>
#include "Graphics.h"
#include "SimpleBorderFactory.h"

using namespace std;

class iControl
{
protected:
	COORD size; //size of the control
	COORD position; //position of the control
	static iControl *focused; // static variable for the control that has focus
	bool visibility; // if the control is visible
	Color backgroundColor;
	Color foregroundColor;
	size_t layer;
	const BorderDrawer *_borderDrawer;

public:
	void setBackground(Color newColor) { backgroundColor = newColor; } //sets the control's background color
	Color getBackground() { return backgroundColor; }
	void setForeground(Color newColor) { foregroundColor = newColor; } //sets the control's foreground color
	Color getForeground(){ return foregroundColor;}
	size_t getLayer() { return layer; }
	virtual void setLayer(size_t newLayer) { layer = newLayer; }
	bool getVisibility() { return visibility; }
	void setVisibility(bool v) { visibility = v; }
	void show() { setVisibility(true); } //show control
	void hide() { setVisibility(false); } //hide control
	iControl(COORD, COORD);
	~iControl() {};
	virtual void draw(Graphics &g, int left, int top, int layer); //implement diffrent draw to each control
	virtual void KeyEventProc(KEY_EVENT_RECORD, HANDLE) = 0; //implement diffrent key event to each control
	virtual void MouseClicked(int left, int top, bool isLeft) {} //implement diffrent mouse enet to each function
	int getHeight() { return size.Y; }
	int getWidth() { return size.X; }
	short getLine() { return position.Y; } //get control's satrt line position
	short getCol() { return position.X; } //get  control's satrt column position
	void setPosition(COORD pos) { position = pos; }
	virtual void getAllControls(vector<iControl*> &vec) //get all the controls that in a panel
	{
		vec.push_back(this);
	}
	static iControl * getFocus() { return focused; } //get the control that has the current focus
	static void setFocus(iControl& i) { if(i.canGetFocus()) focused = &i; } //set the control into foucs
	virtual bool canGetFocus() = 0; // implement if the control can get focus 
	virtual bool innerTab() = 0; //implement if the control has inner tab
	virtual int getCurrnetPos() = 0; // implement the position of the cursor in each control (if there is one)
	virtual void setBorderDrawer(const BorderDrawer &borderDrawer) { _borderDrawer = &borderDrawer; }
	virtual void setBorder(BorderType type) { setBorderDrawer(SimpleBorderFactory::instance().getBorderDrawer(type)); }
};
#endif

