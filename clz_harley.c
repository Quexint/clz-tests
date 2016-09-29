#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "clz_harley.h"

uint8_t clz(uint32_t x) {

	static char table[64] =
	{32,31, 0,16, 0,30, 3, 0,  15, 0, 0, 0,29,10, 2, 0,
		0, 0,12,14,21, 0,19, 0,   0,28, 0,25, 0, 9, 1, 0,
		17, 0, 4, 0, 0, 0,11, 0,  13,22,20, 0,26, 0, 0,18,
		5, 0, 0,23, 0,27, 0, 6,   0,24, 7, 0, 8, 0, 0, 0};

	x = x | (x >> 1);    // Propagate leftmost
	x = x | (x >> 2);    // 1-bit to the right.
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	x = (x << 3) - x;    // Multiply by 7.
	x = (x << 8) - x;    // Multiply by 255.
	x = (x << 8) - x;    // Again.
	x = (x << 8) - x;    // Again.
	return table[x >> 26];
}

