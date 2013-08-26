#include "flame.h"

void effectFlame(void) {
	int yellow[3] = {255, rand() % 51 + 75, rand() % 20 + 1};
	int red = rand() % 16 + 240;

	OCR1A = (yellow[0] + red) / 2;
	OCR1B = yellow[1];
	OCR2 = yellow[2];
}

void effectFlameSetUp(void) {

}
