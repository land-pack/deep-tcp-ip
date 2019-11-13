#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <signal.h>


static int
tap_open(char *dev)
{
    struct ifreq ifr;
    int fd;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0) { return -1; }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if (*dev) strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    if (ioctl(fd, TUNSETIFF, (void *) &ifr) < 0) { goto failed;}

    strcpy(dev, ifr.ifr_name) return fd;

    failed:
        close(fd); return -1;
}

int tapfd;
void 
signal_handler(int sig) { close(tapfd); exit(1); }

int
main(int argc, char * argv[])
{
    unsigned char buf[3200];
    unsigned char name[32];
    int i;
    int numbytes = 0;

    strcpy(name, "tapint");
    tapfd = tap_open(name);
    if (tapfd<0) { prinf("port open error!\n"); return 0; }

    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGINT, signal_handler);

    repeat:
        numbytes = read(tapfd, buf, 2000);
        if (numbytes<=0) { usleep(100); goto repeat;}

        printf("\tTAP Data:");
        for (i=0; i <numbytes; i++) printf("%02x:", buf[i]);

        goto repeat;
        close(tapfd);
    return 0;
}
