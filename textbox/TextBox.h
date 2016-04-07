#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class TextBox {
private:
	string stringInput;
public:
	TextBox();
	~TextBox();
	VOID ErrorExit(LPSTR, HANDLE, DWORD);
	VOID KeyEventProc(KEY_EVENT_RECORD, HANDLE, TextBox*);
	VOID MouseEventProc(MOUSE_EVENT_RECORD, HANDLE);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	VOID SetstringInput(char, int);
	string GetstringInput();
	VOID EraseBackSpace(string, int);
	VOID EraseDel(string, int);
};



#endif