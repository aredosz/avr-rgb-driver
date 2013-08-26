#include "helpers.h"

void turnOffLights(void) {
	OCR1A = 0;
	OCR1B = 0;
	OCR2 = 0;
}

void setUpEffects(int effect) {
	switch (effect) {
	case 0:
		effectStartingSetUp();
		break;

	case 1:
		effectPoliceSetUp();
		break;

	case 2:
		effectSnakeSetUp();
		break;

	case 3:
		effectFlameSetUp();
		break;
	}
}
