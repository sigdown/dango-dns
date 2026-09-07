#ifndef NET_H
#define NET_H

#include <stdint.h>
#include <unistd.h>

int open_udp(void);
ssize_t send_udp(
    int fd,
    const char *ip,
    const uint16_t port,
    const uint8_t *req,
    size_t len
);
ssize_t fetch_udp(int fd, uint8_t *req, size_t len);

#endif