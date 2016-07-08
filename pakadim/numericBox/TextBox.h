#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <Windows.h>
#include <string>
#include "iControl.h"

using namespace std;

class TextBox : public iControl
{
protected:
	//short width;
	//COORD position;
	string stringInput;
public:
	TextBox(short);
	~TextBox() {}
	void draw();
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE);
	void SetChar(string);
	void SetText(string);
	string GetText();
	void EraseBackSpace(string, int);
	void EraseDel(string, int);
};



#endif

