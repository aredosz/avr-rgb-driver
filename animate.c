#include "animate.h"

void setAnimate(struct Animate *a, unsigned int rTo, unsigned int gTo, unsigned int bTo, unsigned int delay, unsigned int ticks) {
	a->rTo = rTo;
	a->gTo = gTo;
	a->bTo = bTo;
	a->delayTicks = delay;
	a->r = OCR1A;
	a->g = OCR1B;
	a->b = OCR2;
	a->rDelta = (rTo - a->r) / ticks;
	a->gDelta = (gTo - a->g) / ticks;
	a->bDelta = (bTo - a->b) / ticks;
}

void nextStep(struct Animate *a) {
	a->open = 0;
	if ((int)a->r != a->rTo || (int)a->g != a->gTo || (int)a->b != a->bTo) {
		if (abs(a->r - a->rTo) > abs(a->rDelta) || abs(a->g - a->gTo) > abs(a->gDelta) || abs(a->b - a->bTo) > abs(a->bDelta)) {
			a->r += a->rDelta;
			a->g += a->gDelta;
			a->b += a->bDelta;
		} else {
			a->r = a->rTo;
			a->g = a->gTo;
			a->b = a->bTo;
		}
	} else {
		if (a->delayTicks) {
			a->delayTicks--;
		} else {
			a->open = 1;
		}
	}

	sendColors((int)a->r, (int)a->g, (int)a->b);
}

void sendColors(int r, int g, int b) {
	OCR1A = r;
	OCR1B = g;
	OCR2 = b;
}

void turnOffLights(void) {
	OCR1A = 0;
	OCR1B = 0;
	OCR2 = 0;
}
