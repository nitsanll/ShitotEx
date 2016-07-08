#include "SingleBorderDrawer.h"
//draw singal border for control using graphics
void SingleBorderDrawer::draw(Graphics &g, int left, int top, int width, int height) const
{
	g.write(left - 1, top - 1, "\xDA");
	for (int i = 0; i < width; i++)
	{
		g.write(left + i, top - 1, "\xC4");
	}
	g.write(left + width, top - 1, "\xBF");
	for (int i = 0; i < height; i++)
	{
		g.write(left - 1, top + i, "\xB3");
		g.write(left + width, top + i, "\xB3");
	}
	g.write(left - 1, top + height, "\xC0");
	for (int i = 0; i < width; i++)
	{
		g.write(left + i, top + height, "\xC4");
	}
	g.write(left + width, top + height, "\xD9");
}