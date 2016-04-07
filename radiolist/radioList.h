#ifndef RadioList_H_
#define RadioList_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class RadioList {

private:
	vector<string> list;
	vector<string> choice;
public:
	RadioList(vector<string>&);
	~RadioList();
	VOID ErrorExit(LPSTR, HANDLE, DWORD);
	VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT, RadioList*);
	VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT, RadioList*);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	void SetList(vector<string>);
	vector<string> GetList();
	void SetChoice(string);
	vector<string> GetChoice();
	VOID eraseChoice(INT);
};


#endif#pragma once
