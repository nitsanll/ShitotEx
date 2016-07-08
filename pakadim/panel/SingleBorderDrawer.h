#ifndef SINGLEBORDERDRAWER_H_
#define SINGLEBORDERDRAWER_H_
#include "BorderDrawer.h"

class SingleBorderDrawer : public BorderDrawer
{
	void draw(Graphics &g, int left, int top, int width, int height) const;
};

#endif