#include "police.h"

void effectPolice(void) {
	if (OCR1A == 0) {
		effectPoliceSgn = -1;
	} else if (OCR1A == 255) {
		effectPoliceSgn = 1;
	}

	OCR1A -= effectPoliceSgn;
	OCR2 += effectPoliceSgn;
}

void effectPoliceSetUp(void) {
	turnOffLights();
	OCR1A = 255;
}
