#ifndef ICONTROLH
#define ICONTROLH
#include<Windows.h>

class iControl
{
private:
	COORD size;
	COORD position;
public:
	iControl(COORD _size, COORD _position) :position(_position), size(_size) {};
	~iControl() {};
	virtual void draw() = 0;
	virtual void KeyEventProc(KEY_EVENT_RECORD, HANDLE, INT) = 0;
	virtual void MouseEventProc(MOUSE_EVENT_RECORD, HANDLE, INT) = 0;
	virtual void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	virtual void ErrorExit(LPSTR, HANDLE, DWORD);
};

#endif