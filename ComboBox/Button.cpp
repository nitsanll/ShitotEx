#include "Label.h"
#include "Button.h"
#include <Windows.h>

Button::Button(int widthNew) :Label(widthNew, "")
{
	//COORD c = { 7, 7 };
	//width = widthNew;
	//draw();
}


void Button::AddListener(MouseListener &newListener)
{
	listeners.push_back(&newListener);
	for (int i = 0; i < listeners.size(); i++) {
			newListener.MousePressed(*this, position.X, position.Y, 1);
	}
}



