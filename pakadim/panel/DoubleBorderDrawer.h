#ifndef DOUBLEBORDERDRAWER_H_
#define DOUBLEBORDERDRAWER_H_
#include "BorderDrawer.h"

class DoubleBorderDrawer : public BorderDrawer {
public:
	void draw(Graphics &g, int left, int top, int width, int height) const;
};

#endif