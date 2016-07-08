#ifndef NUMERICBOX_H_
#define NUMERICBOX_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"
#include "Button.h"
#include "panel.h"
using namespace std;

class NumericBox : public Panel, public MouseListener
{
private:
	int min, max; //the min and max values
	int value; //the current value
	Label label; //the label contains the value
	Button button1; //button for '-'
	Button button2; //button for '+'

public:
	NumericBox(int width, int min, int max);
	~NumericBox() {}
	int GetValue();
	bool SetValue(int value); //sets the new value according to the button pressed
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	bool canGetFocus() { return false; }
	bool innerTab() { return false; }
	int getCurrnetPos() { return -1; }
	void MousePressed(Button &b, int x, int y, bool isLeft);
	void setBackground(Color newColor);
	void setForeground(Color newColor);
};

#endif