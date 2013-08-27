#ifndef GYRMBC_H_
#define GYRMBC_H_

#include <avr/io.h>
#include "../animate.h"

volatile int gyrmbcIndex = 0;

void effectGYRMBC(struct Animate *a);

#endif
