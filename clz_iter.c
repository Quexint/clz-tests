#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "clz_iter.h"

uint8_t clz(uint32_t x) {
	int n = 32, c = 16;
	do {
		uint32_t y = x >> c;
		if (y) { n -= c; x = y; }
		c >>= 1;
	} while (c);
	return (n - x);
}
