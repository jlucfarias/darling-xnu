#include <darling/emulation/xnu_syscall/bsd/impl/xattr/fsctl.h>

#include <sys/errno.h>

#include <darling/emulation/common/base.h>
#include <darling/emulation/conversion/errno.h>
#include <darling/emulation/conversion/fcntl/open.h>
#include <darling/emulation/xnu_syscall/bsd/impl/fcntl/open.h>
#include <darling/emulation/xnu_syscall/bsd/impl/ioctl/ioctl.h>
#include <darling/emulation/xnu_syscall/bsd/impl/unistd/close.h>

long sys_fsctl(const char *path, unsigned long cmd, void* data, unsigned int options)
{
    int fd, ret;
    int flags = BSD_O_RDONLY | BSD_O_NONBLOCK;

    if (options & FSOPT_NOFOLLOW) {
        flags |= BSD_O_NOFOLLOW;
    }

    fd = sys_open(path, flags, 0);
    if (fd < 0)
        return errno_linux_to_bsd(fd);

    // TODO: Verify cmd for unsupported
    // TODO: Verify data if needed

    ret = sys_ioctl(fd, cmd, data);

    sys_close(fd);

    if (ret < 0)
        return errno_linux_to_bsd(ret);

    return ret;
}
