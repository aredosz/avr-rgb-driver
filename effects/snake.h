#ifndef SNAKE_H_
#define SNAKE_H_

#include <avr/io.h>
#include "../animate.h"

volatile int snakeIndex = 0;

void effectSnake(struct Animate *a);

#endif
