#include "net.h"
#include "buffer.h"

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int udp_open(void) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd < 0) {
        perror("failed to open socket");
        return -1;
    }

    return fd;
}

ssize_t udp_send(int fd, const char *ip, const uint16_t port, const dango_buf_t *buf) {
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };

    if (inet_pton(AF_INET, ip, &server.sin_addr) != 1) {
        return -1;
    }

    return sendto(
        fd, 
        buf->data, 
        buf->len, 
        0, 
        (struct sockaddr *)&server, 
        sizeof server
    );
}

ssize_t udp_fetch(int fd, dango_buf_t *buf) {
    ssize_t n = recvfrom(
        fd, 
        buf->data, 
        buf->len, 
        0, 
        NULL, 
        NULL
    );

    if (n < 0)
        return -1;

    buf->len = (size_t)n;

    return n;
}

int udp_close(int fd) {
    if (fd < 0)
        return -1;

    return close(fd);
}