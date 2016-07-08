#ifndef RadioList_H_
#define RadioList_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "CheckList.h"

using namespace std;

class RadioList :public CheckList
{
public:
	RadioList(short, short, vector<string>);
	~RadioList() {}
	VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	size_t GetSelectedIndex(); //get the index that was selected
	bool canGetFocus() { return true; } //radio can get focus
	bool innerTab() { return true; } //radio has an inner tab
	int getCurrnetPos() { return _cursorPosition; } // get the position of the cursor
	void returnFunctionRadio();
	void chooseMouseRadio(int, int);
	void MouseClicked(int left, int top, bool isLeft);

};


#endif
