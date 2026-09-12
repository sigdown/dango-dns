#ifndef NET_H
#define NET_H

#include "buffer.h"

#include <stdint.h>
#include <unistd.h>

int udp_open(void);
ssize_t udp_send(int fd, const char *ip, const uint16_t port, const dango_buf_t *buf);
ssize_t udp_fetch(int fd, dango_buf_t *buf);
int udp_close(int fd);

#endif