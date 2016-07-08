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
	vector<iControl *> controls; //vector contains all the controls in panel

public:
	Panel(short height, short width);
	~Panel();
	virtual void AddiControl(iControl &icontrol, short left, short top); //add control to controls vector
	void setLayer(size_t newLayer);
	void draw(Graphics &g, int left, int top, int layer);
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	virtual void MouseClicked(int left, int top, bool isLeft);
	bool canGetFocus() { return false; }
	int getCurrnetPos() { return -1; }
	void getAllControls(vector<iControl*> &vec) //get all of panel's controls, including itself. push it to vec
	{
		vec.push_back(this);
		for (auto c : controls)
			c->getAllControls(vec);
	}
	bool innerTab() { return false; }
	
};
#endif