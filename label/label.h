#ifndef LABEL_H_ 
#define LABEL_H_
#include <windows.h>
#include <string>
#include <iostream>
#include "iControl.h"

class Label : public iControl
{

private:
	char* input;
public:
	Label(char*);
	~Label() {};
	void KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT) {};
	void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT) {};
	void SetLabel(char*);
	char* GetLabel(void);
	void draw();
};


#endif 