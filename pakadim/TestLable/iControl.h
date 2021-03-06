#ifndef ICONTROLH
#define ICONTROLH
#include<Windows.h>
#include <vector>
#include "Graphics.h"

using namespace std;

class iControl
{
protected:
	COORD size;
	COORD position;
	static iControl *focused;
	bool visibility;
	Color backgroundColor;
	Color foregroundColor;
	size_t layer;
	//const BorderDrawer *_borderDrawer;
public:
	void setBackground(Color newColor) { backgroundColor = newColor; }
	Color getBackground() { return backgroundColor; }
	void setForeground(Color newColor) { foregroundColor = newColor; }
	Color getForeground() { return foregroundColor; }
	size_t getLayer() { return layer; }
	virtual void setLayer(size_t newLayer) { layer = newLayer; }
	bool getVisibility() { return visibility; }
	void setVisibility(bool v) { visibility = v; }
	void show() { setVisibility(true); }
	void hide() { setVisibility(false); }
	iControl(COORD, COORD);
	~iControl() {};
	virtual void draw(Graphics &g, int left, int top, int layer); //implement deffrent draw to each function
	virtual void KeyEventProc(KEY_EVENT_RECORD, HANDLE) = 0; //implement deffrent key event to each function
	virtual void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE) = 0; //implement deffrent mouse enet to each function
	int getHeight() { return size.Y; }
	int getWidth() { return size.X; }
	short getLine() { return position.Y; } //get satrt line position
	short getCol() { return position.X; } //get satrt col position
	void setPosition(COORD pos) { position = pos; }
	virtual void getAllControls(vector<iControl*> &vec) //get all the controls that in the panel
	{
		vec.push_back(this);
	}
	static iControl * getFocus() { return focused; } //get the control that has current focus
	static void setFocus(iControl& i) { focused = &i; } //set the control into foucs
	virtual bool canGetFocus() = 0; // implement if the control can get focus 
	virtual bool innerTab() = 0; //implement if the control has inner tab
	virtual int getCurrnetPos() = 0; // implement the position of the cursor in each control (if there is one)
	virtual void MouseClicked(int left, int top, bool isLeft) {}
	//virtual void setBorderDrawer(const BorderDrawer &borderDrawer) { _borderDrawer = &borderDrawer; }
	//virtual void setBorder(BorderType type) { setBorderDrawer(SimpleBorderFactory::instance().getBorderDrawer(type)); }
};
#endif

