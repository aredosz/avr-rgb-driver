#ifndef ANIMATE_H_
#define ANIMATE_H_

#include <avr/io.h>
#include <stdlib.h>

struct Animate {
	float r,
		  g,
		  b,
		  rDelta,
		  gDelta,
		  bDelta;

	unsigned int open:1,
				 delayTicks,
				 rTo,
				 gTo,
				 bTo;
};

void setAnimate(struct Animate *a, unsigned int rTo, unsigned int gTo, unsigned int bTo, unsigned int delay, unsigned int ticks);
void nextStep(struct Animate *a);
void sendColors(int r, int g, int b);
void turnOffLights(void);

#endif
