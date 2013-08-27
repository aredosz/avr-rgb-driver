#include "police.h"

void effectPolice(struct Animate *a) {
	if (a->open) {
		if (a->r == 255) {
			setAnimate(a, 0, 0, 255, 0, 65);
		} else {
			setAnimate(a, 255, 0, 0, 0, 65);
		}
	}
	nextStep(a);
}
