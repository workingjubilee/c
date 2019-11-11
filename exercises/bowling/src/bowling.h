#ifndef BOWLING_H
#define BOWLING_H

#include <stdint.h>
#include <stdbool.h>

void new_game(void);

bool roll(int16_t points);

int16_t score(void);

#endif