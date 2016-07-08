#ifndef COMBOBOX_H_
#define COMBOBOX_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"
#include "panel.h"
#include "Label.h"
#include "Button.h"
using namespace std;

class Combo : public Panel
{
protected:
	vector<string> list;
	string choice;
	string deafult;
	Label label;
	Button button;
	COORD c[];

public:
	Combo(int width, vector<string> entries);
	~Combo() {};
	vector<string> getList();
	void draw();
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE);
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	void printLines(HANDLE, DWORD, DWORD);
	void eraseLines(int, HANDLE);
	void changeTextColorDown(int, HANDLE, DWORD, DWORD, DWORD, DWORD);
	void changeTextColorUp(int, HANDLE, DWORD, DWORD, DWORD, DWORD);
	size_t GetSelectedIndex();
	void SetSelectedIndex(size_t index);
};

#endif