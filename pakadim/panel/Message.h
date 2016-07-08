#ifndef MESSAGE_H
#define MESSAGE_H
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "iControl.h"
#include "Panel.h"
#include "Button.h"
using namespace std;

class Messagebox : public Panel, public MouseListener
{
private:
	string value; // a string contains the user's choice - 'ok' or 'cancel'
	Label title; //the title of the message box
	Label text; // the text of the message box
	Button ok; // the 'ok' button of the message box
	Button cancel; // the 'cancel' button of the message box
public:
	Messagebox(int height, int width);	~Messagebox() {};	void SetText(string _text);
	void SetTitle(string _title);
	void MousePressed(Button &b, int x, int y, bool isLeft);
	void setBackground(Color newColor);
	void setForeground(Color newColor);
};

#endif
