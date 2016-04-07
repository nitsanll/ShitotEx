#pragma once
#ifndef CHECKLIST_H_
#define CHECKLIST_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class CheckList {

private:
	vector<string> list;
	vector<string> choice;
public:
	CheckList(vector<string>&);
	~CheckList();
	VOID ErrorExit(LPSTR, HANDLE, DWORD);
	VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT, CheckList*);
	VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT, CheckList*);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	void SetList(vector<string>);
	vector<string> GetList();
	void SetChoice(string);
	vector<string> GetChoice();
	VOID eraseChoice(INT);
};


#endif