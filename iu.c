#include <sys/utsname.h>
#include <stdio.h>
#include <liburing.h>


int main(int argc, char **argv)
{
	struct utsname uname_buf;
	int major;
	int minor;
	int rc;
	struct io_uring_probe *probe;

	uname(&uname_buf);
	rc = sscanf(uname_buf.release, "%d.%d-", &major, &minor);
	printf("rc=%d major=%d minor=%d \n", rc, major, minor);

	probe = io_uring_get_probe();
	if (probe == NULL) 
	{
		printf("probe is not supported!\n");
	}
	else
	{
		printf("probe is supported.\n");
	}

	if (io_uring_opcode_supported(probe, IORING_OP_READ)) 
	{ 
		printf("IORING_OP_READ is supported!\n"); 
	} else 
	{ 
		printf("IORING_OP_READ is NOT supported.\n"); 
	} 
	if (io_uring_opcode_supported(probe, IORING_OP_SEND)) 
	{ 
		printf("IORING_OP_SEND is supported!\n"); 
	} else 
	{ 
		printf("IORING_OP_SEND is NOT supported.\n"); 
	} 
	io_uring_free_probe(probe);

}
