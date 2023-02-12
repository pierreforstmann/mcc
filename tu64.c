/*
 * tu64.c
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

static int compare(uint64_t u1, uint64_t u2, uint64_t u3)
{
	printf("u1=%zu u2=%zu u3=%zu u2-u3=%zu u1>u2-u3=%d\n", 
		u1, u2, u3, u2 - u3, u1 > (u2 - u3));
        return (u1 > u2 - u3);
}

int main(int argc, char** argv)
{
	int r;

	r = compare(32769, 32768, 1);
	printf("r=%d\n", r);
}

