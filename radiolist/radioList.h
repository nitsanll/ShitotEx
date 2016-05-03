#ifndef RadioList_H_
#define RadioList_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"

using namespace std;

class RadioList :public iControl
{

private:
	vector<string> list;
	vector<string> choice;
public:
	RadioList();
	~RadioList();
	virtual void draw();
	virtual VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, int);
	virtual VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, int);
	void SetList(vector<string>);
	vector<string> GetList();
	void SetChoice(string);
	vector<string> GetChoice();
	VOID eraseChoice(int);
};


#endif