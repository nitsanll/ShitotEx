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

class Combo : public Panel, public MouseListener
{
protected:
	vector<string> list; // a list of combox's options
	string choice; // the option that was chosen
	string deafult; // deafult option to be chosen
	Label label; // the chosen option will display in the label 
	Button button; //// each option representd by a button
	Panel inner; // an inner panel consists the buttons
	vector<Button*> buttons; // the options buttons vector
	int _cursorPosition; // the line number which the cursor is at
public:
	Combo(int width, vector<string> entries);
	~Combo();
	vector<string> getList(); // get the options list
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE);
	void MousePressed(Button &b, int x, int y, bool isLeft);
	size_t GetSelectedIndex(); // get the index of the chosen option in list vector
	void SetSelectedIndex(size_t index); //set the index of the chosen option in list vector
	bool canGetFocus() { return true; }
	bool innerTab() { return false; }
	int getCurrnetPos() { return -1; }
	void setLayer(size_t newLayer);
	void selectLine(); // function that selects a line from the list vector to be the chosen one
	void setBackground(Color newColor);
	void setForeground(Color newColor);
};

#endif