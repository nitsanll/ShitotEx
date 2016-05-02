#ifndef CHECKLIST_H_
#define CHECKLIST_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"

using namespace std;

class CheckList :public iControl
{

private:
	vector<string> list;
	vector<string> choice;
public:
	CheckList();
	~CheckList();
	virtual void draw();
	virtual VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT, iControl*);
	virtual VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT, iControl*);
	void SetList(vector<string>);
	vector<string> GetList();
	void SetChoice(string);
	vector<string> GetChoice();
	VOID eraseChoice(INT);
};


#endif