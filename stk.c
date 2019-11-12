/*
 * From: https://stackoverflow.com/questions/28715853/error-creating-tun-device-invalid-argument
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>  
#include <sys/ioctl.h>
#include <sys/socket.h> 
#include <linux/if.h>
#include <linux/if_tun.h>

int main(void) {
    char *clonedev = "/dev/net/tun"; 
    int fd, err;
    char * dev_name = "tun0";
    struct ifreq ifr;
   if( (fd = open(clonedev, O_RDWR)) < 0 ) {
        exit(1);
   }
   memset(&ifr, 0, sizeof(ifr));
   strncpy(ifr.ifr_name, dev_name, IFNAMSIZ);
   ifr.ifr_flags = IFF_TUN; 
   printf("Opened %s \n", ifr.ifr_name);
    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
        printf("Failed to creat tun device (errno is %d)\n",
             errno);
        perror("ioctl");
        close(fd);
        exit(1);
   }
   printf("device created");
}
