#include "ft_ping.h"

void sig_handler(int sig)
{
    (void)sig;
    g_stop = 1;
}

double ts_diff_ms(struct timespec *a, struct timespec *b)
{
    return (b->tv_sec - a->tv_sec) * 1000.0 +
           (b->tv_nsec - a->tv_nsec) / 1e6;
}


unsigned short icmp_checksum(void *buf, int len)
{
    unsigned int sum = 0;
    unsigned short *ptr = buf;

    while (len > 1)
    {
        sum += *ptr++;
        len -= 2;
    }
    if (len == 1)
        sum += *(unsigned char *)ptr;

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}