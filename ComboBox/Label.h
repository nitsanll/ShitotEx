#ifndef LABEL_H_ 
#define LABEL_H_
#include <windows.h>
#include <string>
#include <iostream>
#include "TextBox.h"

class Label : public TextBox
{

protected:
	int width;
	//string input;
public:
	Label() :TextBox(0) {};
	Label(int, string);
	~Label() {};
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE) {}
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE) {}
	void draw();
};


#endif 
