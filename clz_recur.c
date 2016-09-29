#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "clz_recur.h"

#define MASK(x) ((1LL << (x)) - 1)
uint8_t clz(uint32_t x)
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
//	uint32_t lower = (x >> tailingF) & MASK(range);
	return upper ? clz(x | MASK(tailingF + range))  :
			range + clz((x << range) | MASK(range));
}
