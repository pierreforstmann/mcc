/*
 * tpf.c
 *
 * translate process flag
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
#include <limits.h>

#define MAX_PF			100

/*
 * from <linux/sched.h>
 */

#define PF_IDLE			0x00000002	/* I am an IDLE thread */
#define PF_EXITING		0x00000004	/* Getting shut down */
#define PF_VCPU			0x00000010	/* I'm a virtual CPU */
#define PF_WQ_WORKER		0x00000020	/* I'm a workqueue worker */
#define PF_FORKNOEXEC		0x00000040	/* Forked but didn't exec */
#define PF_MCE_PROCESS		0x00000080      /* Process policy on mce errors */
#define PF_SUPERPRIV		0x00000100	/* Used super-user privileges */
#define PF_DUMPCORE		0x00000200	/* Dumped core */
#define PF_SIGNALED		0x00000400	/* Killed by a signal */
#define PF_MEMALLOC		0x00000800	/* Allocating memory */
#define PF_NPROC_EXCEEDED	0x00001000	/* set_user() noticed that RLIMIT_NPROC was exceeded */
#define PF_USED_MATH		0x00002000	/* If unset the fpu must be initialized before use */
#define PF_USED_ASYNC		0x00004000	/* Used async_schedule*(), used by module init */
#define PF_NOFREEZE		0x00008000	/* This thread should not be frozen */
#define PF_FROZEN		0x00010000	/* Frozen for system suspend */
#define PF_KSWAPD		0x00020000	/* I am kswapd */
#define PF_MEMALLOC_NOFS	0x00040000	/* All allocation requests will inherit GFP_NOFS */
#define PF_MEMALLOC_NOIO	0x00080000	/* All allocation requests will inherit GFP_NOIO */
#define PF_LOCAL_THROTTLE	0x00100000	/* Throttle writes only against the bdi I write to */
#define PF_KTHREAD		0x00200000	/* I am a kernel thread */
#define PF_RANDOMIZE		0x00400000	/* Randomize virtual address space */
#define PF_SWAPWRITE		0x00800000	/* Allowed to write to swap */
#define PF_NO_SETAFFINITY	0x04000000	/* Userland is not allowed to meddle with cpus_mask */
#define PF_MCE_EARLY		0x08000000      /* Early kill for mce process policy */
#define PF_MEMALLOC_NOCMA	0x10000000	/* All allocation request will have _GFP_MOVABLE cleared */
#define PF_IO_WORKER		0x20000000	/* Task is an IO worker */
#define PF_MUTEX_TESTER		0x20000000	/* Thread belongs to the rt mutex tester */
#define PF_FREEZER_SKIP		0x40000000	/* Freezer should not count it as freezable */
#define PF_SUSPEND_TASK		0x80000000      /* This thread called freeze_processes() and should not be frozen */

static void check64(uint64_t u)
{
	int i;
	int last_match_index ;
	uint64_t match[MAX_PF];
	uint64_t sum;
	/*
	 * kernel 4.18
	 */
	static uint64_t fa[] = {
		PF_IDLE,
		PF_EXITING,
		PF_VCPU,
		PF_WQ_WORKER,
		PF_FORKNOEXEC,
		PF_MCE_PROCESS,
		PF_SUPERPRIV,
		PF_DUMPCORE,
		PF_SIGNALED,
		PF_MEMALLOC,
		PF_NPROC_EXCEEDED,
		PF_USED_MATH,
		PF_USED_ASYNC,
		PF_NOFREEZE,
		PF_FROZEN,
		PF_KSWAPD,
		PF_MEMALLOC_NOFS,
		PF_MEMALLOC_NOIO,
		PF_LOCAL_THROTTLE,
		PF_KTHREAD,
		PF_RANDOMIZE,
		PF_SWAPWRITE,
		PF_NO_SETAFFINITY,
		PF_MCE_EARLY,
		PF_MEMALLOC_NOCMA,
		PF_IO_WORKER,
		PF_MUTEX_TESTER,
		PF_FREEZER_SKIP,
		PF_SUSPEND_TASK

	};

	printf("\n");
	printf("input = %lu\n", u);
	sum = 0;
	last_match_index = 0;
	for (i = 0; i < MAX_PF; i++)
		match[i] = 0;
	for (i = 0; i < sizeof(fa)/sizeof(uint64_t); i++)
		if ((fa[i] & u) == fa[i])
		{
			match[i] = 1;	
			last_match_index = i;
		}		

	for (i = 0; i < sizeof(fa)/sizeof(uint64_t); i++)
		if (match[i] == 1)
			sum += fa[i];
	if (sum == u)
	{
		printf("OK: %lu = ", u);
		for (i = 0; i < sizeof(fa)/sizeof(uint64_t); i++)
		{
			if (match[i] == 1)
			{
				printf(" %lu ", fa[i]);
				if (i != last_match_index)
					printf(" + ");
			}
		}	
		printf("\n");
	}
	else	 
	{
		printf("ERROR: %lu <> ", u);
		for (i = 0; i < sizeof(fa)/sizeof(uint64_t); i++)
		{
			if (match[i] == 1)
			{
				printf(" %lu ", fa[i]);
				if (i != last_match_index)
					printf(" + ");
			}
		}
		printf("... %lu \n", sum);
	}
}

int main(int argc, char **argv)
{
	uint64_t u64;

	if (argc != 2)
	{
		printf("Usage: pf <process flag>\n");
		exit(1);
	}
	errno = 0;
	u64 = strtol(argv[1], NULL, 10);
	if (errno != 0)
	{
		perror("strtol");
		exit(1);
	}
	check64(u64);

}

