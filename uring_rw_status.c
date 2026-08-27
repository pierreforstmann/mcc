/*
 * uring_rw_status.c
 *
 * from https://commitfest.postgresql.org/patch/6428/
 *
 * HAVE_IO_URING_OPCOCDE_SUPPORTED flag must be define at compile time
 */

#include <stdio.h>

#include <sys/mman.h>
#include <sys/utsname.h>
#include <unistd.h>

#include <liburing.h>


/*
 * Check if the kernel supports the required io_uring operations.
 *
 * PostgreSQL requires four io_uring opcodes:
 *   - IORING_OP_READ and IORING_OP_WRITE (added in kernel 5.6)
 *   - IORING_OP_READV and IORING_OP_WRITEV (added in kernel 5.1)
 *
 * While io_uring was introduced in Linux 5.1 with vectored operations,
 * the non-vectored READ/WRITE opcodes weren't added until 5.6. Since
 * PostgreSQL uses all four, we need kernel 5.6+.
 *
 * Rather than checking kernel version (which is unreliable due to vendor
 * backports), we probe for actual opcode support when possible.
 *
 * Returns true if any required opcode is NOT supported.
 */
static bool
is_uring_read_write_unsupported(void)
{
	struct io_uring test_ring;
#ifdef HAVE_IO_URING_OPCODE_SUPPORTED
        struct io_uring_probe *test_probe;
#endif
	int			ret;
	bool		unsupported = false;

	/* Create a temporary ring to probe capabilities */
	ret = io_uring_queue_init(2, &test_ring, 0);
	if (ret < 0)
	{
		/*
		 * If we can't even create a ring, let the normal initialization path
		 * handle the error with appropriate messages.
		 */
		return false;
	}

#ifdef HAVE_IO_URING_OPCODE_SUPPORTED
	/*
	 * Use io_uring_opcode_supported() if available (liburing 2.1+).
	 * This directly queries the kernel for opcode support.
	 *
	 * PostgreSQL uses both single-buffer (READ/WRITE) and vectored
	 * (READV/WRITEV) operations. READV/WRITEV were added in kernel 5.1,
	 * but READ/WRITE were added in kernel 5.6. Check for all four to
	 * ensure complete support.
	 */
        test_probe = io_uring_get_probe();
        if (test_probe == NULL) 
        {
            return true;
        }
	if (!io_uring_opcode_supported(test_probe, IORING_OP_READ) ||
		!io_uring_opcode_supported(test_probe, IORING_OP_WRITE) ||
		!io_uring_opcode_supported(test_probe, IORING_OP_READV) ||
		!io_uring_opcode_supported(test_probe, IORING_OP_WRITEV))
	{
		unsupported = true;
	}
#else
	/*
	 * Fallback: Try to probe by checking if we can prepare read operations.
	 * Kernels without IORING_OP_READ support will fail later, but at least
	 * we tried. This is less reliable but works with older liburing.
	 */
	{
		struct io_uring_sqe *sqe;

		sqe = io_uring_get_sqe(&test_ring);
		if (sqe)
		{
			/*
			 * Prepare a dummy read operation. On kernels without
			 * IORING_OP_READ support, this will be accepted here but fail
			 * with EINVAL when submitted. We'd need to actually submit to
			 * detect, but that requires a valid fd. The version check is a
			 * reasonable fallback.
			 */
			struct utsname uts;
			int			major,
						minor;

			if (uname(&uts) == 0 &&
				sscanf(uts.release, "%d.%d", &major, &minor) == 2)
			{
				/* Known problematic kernel range */
				if (major == 5 && minor >= 1 && minor <= 5)
					unsupported = true;
			}
		}
	}
#endif

	io_uring_queue_exit(&test_ring);
	return unsupported;
}

int main(int argc, char **argv) 
{
    bool rc;

    printf("io_uring_version: %d.%d \n", io_uring_major_version(), io_uring_minor_version());

    rc = is_uring_read_write_unsupported();
    if (rc)
        printf("is_uring_read_write_unsupported: true\n");
    else
        printf("is_uring_read_write_unsupported: false\n");

}

