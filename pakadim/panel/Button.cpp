#include "Label.h"
#include "Button.h"
#include <Windows.h>

//function that adds iControl that had button to it's listeners array
void Button::AddListener(MouseListener &newListener)
{
	listeners.push_back(&newListener);
}

void Button::draw(Graphics &g, int left, int top, int layer)
{
	Label::draw(g, left, top, layer);
}

//function that is activated when mouse clicked the button, goes over the listeners array activating mouse press
void Button::MouseClicked(int left, int top, bool isLeft)
{
	for (auto l : listeners)
		l->MousePressed(*this, left, top, isLeft);
}

