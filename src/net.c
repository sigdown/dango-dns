#include "net.h"

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int open_udp(void) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd < 0) {
        perror("failed to open socket");
        return -1;
    }

    return fd;
}

ssize_t send_udp(
    int fd, 
    const char *ip, 
    const uint16_t port, 
    const uint8_t *req,
    size_t len
) {
    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };

    if (inet_pton(AF_INET, ip, &server.sin_addr) != 1) {
        return -1;
    }

    return sendto(
        fd, 
        req, 
        len, 
        0, 
        (struct sockaddr *)&server, 
        sizeof server
    );
}

ssize_t fetch_udp(int fd, uint8_t *res, size_t len) {
    ssize_t n = recvfrom(
        fd, 
        res, 
        len, 
        0, 
        NULL, 
        NULL
    );

    return n;
}

int close_udp(int fd) {
    if (fd < 0) {
        perror("failed to close socket");
        return -1;
    }

    close(fd);
}