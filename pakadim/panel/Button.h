#ifndef BUTTON_H_ 
#define BUTTON_H_
#include <windows.h>
#include <string>
#include <iostream>
#include "Label.h"
#include <vector>

struct MouseListener;

class Button : public Label
{
protected:
	int width;
	vector<MouseListener*> listeners;

public:
	Button() :Label(0, "") {};
	Button(int newWidth) :Label(newWidth, "") {};
	~Button() {};
	void AddListener(MouseListener &listener); //function that add iControl that had button, and go over aray activating mouse press
	bool canGetFocus() { return false; } // button can't get focus
	bool innerTab() { return true; } //dosn't have inner tab to press on
	int getCurrnetPos() { return -1; }	//dosen't have posintion
	void draw(Graphics &g, int left, int top, int layer);
	void MouseClicked(int left, int top, bool isLeft);
};

//implement MousePressed for the controls that have button
struct MouseListener
{
	virtual void MousePressed(Button &b, int x, int y, bool isLeft) = 0;
};

#endif 