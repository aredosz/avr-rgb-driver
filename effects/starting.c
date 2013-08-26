#include "starting.h"

void effectStarting(void) {
	OCR1A = effectStartingIncrement(OCR1A);
	OCR1B = effectStartingIncrement(OCR1B);
	OCR2 = effectStartingIncrement(OCR2);
}

int effectStartingIncrement(int value) {
	if (value < 255) {
		return value + 1;
	}
	return value;
}

void effectStartingSetUp(void) {
	turnOffLights();
}
