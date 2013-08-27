#include "flame.h"

void effectFlame(struct Animate *a) {
	int yellow[3] = {255, rand() % 51 + 75, rand() % 10 + 1};
	int red = rand() % 16 + 240;

	if (a->open) {
		setAnimate(a, (yellow[0] + red) / 2, yellow[1], yellow[2], 0, 15);
	}
	nextStep(a);
}
