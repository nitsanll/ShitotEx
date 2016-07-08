#ifndef NULLBORDERDRAWER_H_
#define NULLBORDERDRAWER_H_
#include "BorderDrawer.h"

class NullBorderDrawer : public BorderDrawer {
public:
	void draw(Graphics &g, int left, int top, int width, int height) const { } //no need to draw a border
};

#endif