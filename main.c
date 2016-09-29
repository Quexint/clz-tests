#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include IMPL

int main()
{
	int i, ret;
	for (i = 0; i < (1<<20); i++) {
		ret = clz(i);
		/* Bacause __builtin_clz(0) == 31 */
		if(i)assert(ret == __builtin_clz(i));
	}
	return 0;
}
