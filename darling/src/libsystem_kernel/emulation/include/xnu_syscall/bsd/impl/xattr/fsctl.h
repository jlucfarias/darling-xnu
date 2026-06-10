#ifndef LINUX_FSCTL_H
#define LINUX_FSCTL_H

/* Commands */
#define FSGETMOUNTINFOSIZE

/* Options */
#define FSOPT_NOFOLLOW  0x00000001 /* Don't follow symlinks */

long sys_fsctl(const char *path, unsigned long cmd, void* data, unsigned int options);

#endif // LINUX_FSCTL_H
