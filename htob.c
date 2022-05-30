/*
 * htob.c
 *
 * display hexadecimal in bit string
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>


static void dump8(uint8_t u)
{
	uint8_t i;

	printf("\n");
	printf("input=0x%x\n", u);
	printf("output=");
	for (i=0; i < 8; i++)
		if ((u & ( 1 <<i)) == 0)
			printf("0");	
		else 	printf("1");
	printf("\n");
}

static void dump16(uint16_t u)
{
	uint16_t i;

	printf("\n");
	printf("input=0x%x\n", u);
	printf("output=");
	for (i=0; i < 16; i++)
		if ((u & ( 1 <<i)) == 0)
			printf("0");	
		else 	printf("1");
	printf("\n");
}

static void dump32(uint32_t u)
{
	uint32_t i;

	printf("\n");
	printf("input=0x%x\n", u);
	printf("output=");
	for (i=0; i < 32; i++)
		if ((u & ( 1 <<i)) == 0)
			printf("0");	
		else 	printf("1");
	printf("\n");
}

/*
 * see
 * https://stackoverflow.com/questions/14846566/how-to-shift-32-bits-in-uint64-t
 */
static void dump64_ko(uint64_t u)
{
	uint64_t i;
	
	printf("\n");
	printf("input=0x%lx\n", u);
	printf("output=");
	for (i=0; i < 64; i++)
	{
		if ((u & ( 1 <<i)) == 0)
			printf("0");	
		else 	printf("1");
		
	}
	printf("\n");

	for (i=0; i < 64; i++)
	{
		printf("i=%lu result=%lu\n", i, (u & (1 << i)));	
		
	}

}

static void dump64(uint64_t u)
{
	uint64_t i;
	uint64_t one = 1;
	
	printf("\n");
	printf("input=0x%lx\n", u);
	printf("output=");
	for (i=0; i < 64; i++)
	{
		if ((u & ( one <<i)) == 0)
			printf("0");	
		else 	printf("1");
		
	}
	printf("\n");
}

static void test()
{
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;

	u8=0xfe;
	dump8(u8);

	u16 = 0xfffe;
	dump16(u16);

	u32 = 0xfffffffe;
	dump32(u32);

	u64 = 0xfffffffffffffffe;
	dump64_ko(u64);
	dump64(u64);

}

int main(int argc, char **argv)
{
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;

	if (argc != 2)
	{
		printf("Usage: htob <hexa. number>\n");
		exit(1);
	}
	if ((argv[1][0] != '0') && (argv[1][1] != 'x'))
	{
		printf("Usage: htob 0x...\n");
		test();
		exit(1);
	}
	printf(" UINT8_MAX = %u = 0x%x\n", UINT8_MAX, UINT8_MAX);
	printf("UINT16_MAX= %u = 0x%x\n", UINT16_MAX, UINT16_MAX);
	printf("UINT32_MAX= %u = 0x%x\n", UINT32_MAX, UINT32_MAX);
	printf("UINT64_MAX= %lu = 0x%lx\n", UINT64_MAX, UINT64_MAX);
	printf("\n");
	printf("argv[1] has %lu hexa. digits\n", strlen(argv[1]) - 2);
		
	errno = 0;
	u64 = strtoll(argv[1], NULL, 16);
	if (errno != 0)
	{
		perror("strtoll");
		exit(1);
	}
	if (u64 <= UINT8_MAX)
	{
		u8 = (uint8_t)u64;
		dump8(u8);
	} else if (u64 <= UINT16_MAX)
	{
		u16 = (uint16_t)u64;
		dump16(u16);
	} else if (u64 <= UINT32_MAX)
	{
		u32 = (uint32_t)u64;
		dump32(u32);
	} else dump64(u64);

}

