/*
 * open: O_RDONLY
 *
 * (C) 2019.12.24 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
	char buffer[20];
	int fd, ret;

	/* open */
	fd = open("/etc/fstab", O_RDONLY);
	if (fd < 0) {
		perror("/etc/fstable");
		return -1;
	}
	/* Read operation */
	memset(buffer, 0, 20);
	ret = read(fd, buffer, 10);
	if (ret < 0) {
		perror("Read failed");
		close(fd);
		return -1;
	}
	buffer[10] = '\0';
	printf("Read contents: %s\n", buffer);

	/* Force write with Read_Only */
	ret = write(fd, buffer, 10);
	if (ret < 0) {
		perror("Write failed");
		close(fd);
		return -1;
	}

	/* close */
	close(fd);

	return 0;
}
