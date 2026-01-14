/*
 * taio.c
 * 
 * test AIO on Linux
 * 
 * taio <number of operations for io_setup> <number of control blocks for io_submit>
 *
 *
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <linux/aio_abi.h>



inline int io_setup(unsigned nr, aio_context_t *ctxp) {
	return syscall(__NR_io_setup, nr, ctxp);
}

inline int io_destroy(aio_context_t ctx) {
	return syscall(__NR_io_destroy, ctx);
}

inline int io_submit(aio_context_t ctx, long nr, struct iocb **iocbpp) {
	return syscall(__NR_io_submit, ctx, nr, iocbpp);
}

inline int io_getevents(aio_context_t ctx, long min_nr, long max_nr,
		struct io_event *events, struct timespec *timeout) {
	return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}

/*
 * size must match
 */
#define IO_SIZE 20 

int main(int argc, char *argv[]) {
	aio_context_t ctx;
	struct iocb *tcb;
	struct iocb **lcb;
	char *data;
	char **tdata;
	struct io_event *events;
	int ret;
	int fd;
        int i,j;
	long int nr_iosetup;
	long int nr_iosubmit;
	int current_offset;

	if (argc != 1 && argc != 3)
	{
		printf("taio: usage <number of operations for io_setup> <number of control blocks for io_submit>");
		return 1;
	}

	nr_iosetup = 1;
	nr_iosubmit = 1;
	for(i=0; i < argc; i++)
	{
		if (i == 1)
			nr_iosetup = atoi(argv[1]);
		if (i == 2)
			nr_iosubmit = atoi(argv[2]);
	}

	tdata = malloc(nr_iosubmit * sizeof(char *));
	if (tdata == NULL)	
	{
		perror("malloc tdata");
		return 1;
	}

	tcb = malloc(nr_iosubmit * sizeof(struct iocb));
	if (tcb == NULL)	
	{
		perror("malloc tcb");
		return 1;
	}

	lcb = malloc(nr_iosubmit * sizeof(struct iocb *));
	if (lcb == NULL)	
	{
		perror("malloc lcb");
		return 1;
	}

	for (j=0; j < nr_iosubmit; j++)
	{
		data = malloc(IO_SIZE);
		if (data == NULL)
		{
			perror("malloc data");
			return 1;
		}
		tdata[j] = data;
		sprintf(data, "%d\n", j);
	}

	events = malloc(nr_iosubmit * sizeof(struct io_event));
	if (events == NULL)	
	{
		perror("malloc events");
		return 1;
	}
	

	ret = unlink("/tmp/taio.dat");
	/* ignore error */

	fd = open("/tmp/taio.dat", O_RDWR | O_CREAT | O_EXCL,  S_IRWXU);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	printf("open\t\t=> fd=%d\n", fd);

	ctx = (aio_context_t)0;
	ret = io_setup(nr_iosetup, &ctx);
	if (ret < 0) {
		perror("io_setup");
		return -1;
	}
	printf("io_setup\t=> nr_iosetup=%ld ret=%d\n", nr_iosetup, ret);


	/* command-specific options */
	for (j=0, current_offset=0; j < nr_iosubmit; j++)
	{
        	/* setup I/O control block */
		memset(&tcb[j], 0, sizeof(struct iocb));
		tcb[j].aio_fildes = fd;
		tcb[j].aio_lio_opcode = IOCB_CMD_PWRITE;
		tcb[j].aio_buf = (uint64_t)tdata[j];
		tcb[j].aio_offset = current_offset;
		tcb[j].aio_nbytes = IO_SIZE;

		lcb[j] = &tcb[j];
		
		current_offset += IO_SIZE;
	}

	ret = io_submit(ctx, nr_iosubmit, lcb);
	if (ret < 0) 
	{
		perror("io_submit");
		return 1;
	}

	printf("io_submit\t=> nr_iosubmit=%ld ret=%d\n", nr_iosubmit, ret);

	ret = io_getevents(ctx, nr_iosubmit, nr_iosubmit, events, NULL);
	printf("io_getevents\t=> ret=%d\n", ret);

	ret = io_destroy(ctx);
	if (ret < 0) {
		perror("io_destroy");
		return -1;
	}
	printf("io_destroy\t=> ret=%d\n", ret);

	return 0;
}
