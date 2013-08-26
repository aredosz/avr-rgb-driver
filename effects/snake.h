#ifndef SNAKE_H_
#define SNAKE_H_

#include <avr/io.h>

volatile int snakeRising = 1;

void effectSnake(void);
void effectSnakeSetUp(void);

#endif
