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

class NumericBox : public Panel
{
private:
	int min, max;
	int value;
	Label label;
	Button button1;
	Button button2;

public:
	NumericBox(int width, int min, int max);
	~NumericBox() {}
	int GetValue();
	bool SetValue(int value);
	void draw();
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE);
};

#endif