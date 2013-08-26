#include "snake.h"

void effectSnake(void) {
	if (snakeRising == 0) {
		if (OCR1A < 255) {
			OCR1A += 1;
		}
		if (OCR1A > 127 && OCR1B < 255) {
			OCR1B += 1;
		}
		if (OCR1A > 127 && OCR1B > 127 && OCR2 < 255) {
			OCR2 += 1;
		}
		if (OCR1A == 255 && OCR1B == 255 && OCR2 == 255) {
			snakeRising = 1;
		}
	} else {
		if (OCR1A > 0) {
			OCR1A -= 1;
		}
		if (OCR1A < 127 && OCR1B > 0) {
			OCR1B -= 1;
		}
		if (OCR1A < 127 && OCR1B < 127 && OCR2 > 0) {
			OCR2 -= 1;
		}
		if (OCR1A == 0 && OCR1B == 0 && OCR2 == 0) {
			snakeRising = 0;
		}
	}
}

void effectSnakeSetUp(void) {
	turnOffLights();
}
