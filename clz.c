#include <stdint.h>
#include "clz.h"

uint8_t clz_byteshift(uint32_t x) {
	if (x == 0) return 32;
	int n = 1;
	if ((x >> 16) == 0) { n += 16; x <<= 16; }
	if ((x >> 24) == 0) { n += 8; x <<= 8; }
	if ((x >> 28) == 0) { n += 4; x <<= 4; }
	if ((x >> 30) == 0) { n += 2; x <<= 2; }
	n = n - (x >> 31);
	return n;
}

uint8_t clz_bsearch(uint32_t x) {
	if (x == 0) return 32;
	int n = 0;
	if (x <= 0x0000FFFF) { n += 16; x <<= 16; }
	if (x <= 0x00FFFFFF) { n += 8; x <<= 8; }
	if (x <= 0x0FFFFFFF) { n += 4; x <<= 4; }
	if (x <= 0x3FFFFFFF) { n += 2; x <<= 2; }
	if (x <= 0x7FFFFFFF) { n += 1; x <<= 1; }
	return n;
}

#define MASK(x) ((1LL << (x)) - 1)
uint8_t clz_recur(uint32_t x)
{
	if(x == 0xFFFFFFFF) return 0;
	if(x == 0x7FFFFFFF) return 1;
	uint8_t tailingF = (0x0000FFFF == (x & 0x0000FFFF)) * 16 +
										 (0x00FFFFFF == (x & 0x00FFFFFF)) * 8 +
										 (0x0FFFFFFF == (x & 0x0FFFFFFF)) * 4 +
										 (0x3FFFFFFF == (x & 0x3FFFFFFF)) * 2 +
										 (0x7FFFFFFF == (x & 0x7FFFFFFF)) * 1;
	uint8_t range = (32 - tailingF)>>1;

	uint32_t upper = (x >> tailingF) >> range;
	return upper ? clz_recur(x | MASK(tailingF + range))  :
			range + clz_recur((x << range) | MASK(range));
}

uint8_t clz_iter(uint32_t x) {
	int n = 32, c = 16;
	do {
		uint32_t y = x >> c;
		if (y) { n -= c; x = y; }
		c >>= 1;
	} while (c);
	return (n - x);
}

uint8_t clz_harley(uint32_t x) {

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

