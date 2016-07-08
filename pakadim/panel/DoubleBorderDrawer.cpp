#include "DoubleBorderDrawer.h"
//draw double border for control using graphics
void DoubleBorderDrawer::draw(Graphics &g, int left, int top, int width, int height) const
{
	g.write(left - 1, top - 1, "\xC9");
	for (int i = 0; i < width; i++)
	{
		g.write(left + i, top - 1, "\xCD");
	}
	g.write(left + width, top - 1, "\xBB");
	for (int i = 0; i < height; i++)
	{
		g.write(left - 1, top + i, "\xBA");
		g.write(left + width, top + i, "\xBA");
	}
	g.write(left - 1, top + height, "\xC8");
	for (int i = 0; i < width; i++)
	{
		g.write(left + i, top + height, "\xCD");
	}
	g.write(left + width, top + height, "\xBC");
}