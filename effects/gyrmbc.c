#include "gyrmbc.h"

void effectGYRMBC(struct Animate *a) {
	int colors[6][3] = {{0, 255, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 255}, {0, 0, 255}, {0, 255, 255}};

	if (a->open) {
		setAnimate(a, colors[gyrmbcIndex][0], colors[gyrmbcIndex][1], colors[gyrmbcIndex][2], 180, 120);
		gyrmbcIndex = (gyrmbcIndex + 1) % 6;
	}
	nextStep(a);
}
