#ifndef LABEL_H_ 
#define LABEL_H_
#include <windows.h>
#include <string>
#include <iostream>
#include "TextBox.h"
class Label : public TextBox
{
public:
	Label() :TextBox(0) {};
	Label(int, string);
	~Label() {};
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE) {}
	void MouseClicked(int left, int top, bool isLeft) {}
	bool canGetFocus() { return false; }
	bool innerTab() { return false; }
	int getCurrnetPos() { return -1; }
};
#endif