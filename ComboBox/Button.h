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
	Button(int);
	~Button() {};
	void AddListener(MouseListener &listener);
};

struct MouseListener
{
	virtual void MousePressed(Button &b, int x, int y, bool isLeft) = 0;
};

#endif 
