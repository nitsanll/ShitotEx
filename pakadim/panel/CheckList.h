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
protected:
	vector<string> list; //the list that was send
	vector<string> choice; //the list that was selected
	int _cursorPosition; //current position of the cursor

public:
	CheckList(short, short, vector<string>); //constructor
	~CheckList() {};
	void draw(Graphics &g, int left, int top, int layer);
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	vector<size_t> GetSelectedIndices();
	void SelectIndex(size_t index);
	void DeselectIndex(size_t index);
	bool canGetFocus() { return true; } //checklist can get focus
	bool innerTab() { return true; }	//checklist has inner tab to go over the list
	int getCurrnetPos() { return _cursorPosition; } //get position of the  cursor
	void upFunction();
	void downFunction();
	void tabFunction();
	void returnFunctionList();
	void chooseMouseList(int, int);
	void MouseClicked(int left, int top, bool isLeft);
};

#endif