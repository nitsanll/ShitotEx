#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <Windows.h>
#include <string>
#include "iControl.h"

using namespace std;

class TextBox: public iControl 
{
private:
	string stringInput;
public:
	TextBox();
	~TextBox() {}
	void draw();
	VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT);
	VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT);
	VOID SetstringInput(char, int);
	string GetstringInput();
	VOID EraseBackSpace(string, int);
	VOID EraseDel(string, int);
};



#endif