#ifndef COMBOBOX_H_
#define COMBOBOX_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"
using namespace std;

class Combo : public iControl
{
private:
	vector<string> list;
	string choice;
	string deafult; 
	//COORD currentPos = { 7,7 };
	COORD c[];

public:
	Combo(vector<string> entries);
	~Combo();
	vector<string> getList();
	void draw();
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, int);
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE, int);
	void printLines(HANDLE, DWORD, DWORD);
	void eraseLines(string, int, HANDLE);
	void changeTextColorDown(int, HANDLE, DWORD, DWORD, DWORD, DWORD);
	void changeTextColorUp(int, HANDLE, DWORD, DWORD, DWORD, DWORD);
	size_t GetSelectedIndex();
	void SetSelectedIndex(size_t index);
};

#endif