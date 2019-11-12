/*
 * Taken from Kernel Documentation/networking/tuntap.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int
tun_alloc(char *dev)
{
	struct ifreq ifr;
	int fd, err;
	
	if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
		printf("Cannot open TUN/TAP dev");
		exit(1);
	}
	return fd;
}

int 
main(int argc, char *argv[])
{
	char dev[] = "test";
	int fd;
	fd  = tun_alloc(dev);
        printf("fd=%d\n", fd);
	return 0;
}
