#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <Windows.h>
#include <string>
#include "iControl.h"

using namespace std;

class TextBox : public iControl
{
private:
	int _cursorPosition;
protected:
	string stringInput;
public:
	TextBox(short);
	~TextBox() {}
	void draw(Graphics &g, int left, int top, int layer);
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	void SetText(string);
	string GetText();
	bool canGetFocus() { return true; } //textbox can get focus
	bool innerTab() { return false; } //textbox dosen't have inner tab
	int getCurrnetPos() { return _cursorPosition; } //return current position of the cursor
	void MouseClicked(int left, int top, bool isLeft);
};

#endif