#ifndef PANEL_H_ 
#define PANEL_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"
using namespace std;

class Panel : public iControl {

protected:
	int width;
	int height;
	//COORD currentPos;
	vector<iControl *> controls;

public:
	Panel(short height, short width);
	~Panel();
	//virtual void AddiControl(iControl &icontrol);
	virtual void AddiControl(iControl &icontrol, short left, short top);
	//int getCurrentLine();
	void draw();
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE) {}
	//void SetText(string) {}
	//void addPanel(Panel& panel);
	/*Panel& operator=(const Panel &rhs)
	{
	*this = static_cast<const iControl&>(rhs);
	j = rhs.j;
	return *this;
	}*/
};

#endif