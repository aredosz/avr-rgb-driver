#include "snake.h"

void effectSnake(struct Animate *a) {
	int colors[6][3] = {{50, 255, 255}, {50, 50, 255}, {50, 50, 50}, {255, 50, 50}, {255, 255, 50}, {255, 255, 255}};

	if (a->open) {
		setAnimate(a, colors[snakeIndex][0], colors[snakeIndex][1], colors[snakeIndex][2], 0, 180);
		snakeIndex = (snakeIndex + 1) % 6;
	}
	nextStep(a);
}
