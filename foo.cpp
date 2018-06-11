#include "Terminal.h"

int main() {
	Terminal t;
	PixelMatrix pxm(100, 100, RGB::CYAN);
	t.paint(pxm);
	t.getKey();
	pxm.paint(3, 15, RGB::BLUE);
	t.paint(pxm);
	t.getKey();
	return 0;
}
