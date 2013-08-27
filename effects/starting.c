#include "starting.h"

void effectStarting(struct Animate *a) {
	if (a->open) {
		setAnimate(a, 255, 255, 255, 0, 65);
	}
	nextStep(a);
}
