#ifndef LABEL_H_ 
#define LABEL_H_
#include <windows.h>
#include <string>
#include <iostream>

class Label
{

private:
	char* input;
public:
	Label(char*);
	~Label();
	VOID ErrorExit(LPSTR, HANDLE, DWORD);
	VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	VOID SetLabel(char*);
	char* GetLabel(void);
};


#endif 