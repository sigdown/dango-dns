#include "dns.h"
#include "io.h"
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv) {

    uint8_t buf[512];

    size_t offset = 0;

    // header

    buf[offset++] = 0x12;
    buf[offset++] = 0x34;

    buf[offset++] = 0x01;
    buf[offset++] = 0x00;

    buf[offset++] = 0x00;
    buf[offset++] = 0x01;

    buf[offset++] = 0x00;
    buf[offset++] = 0x00;

    buf[offset++] = 0x00;
    buf[offset++] = 0x00;

    buf[offset++] = 0x00;
    buf[offset++] = 0x00;

    // question

    buf[offset++] = 7;
    memcpy(buf + offset, "sigdown", 7);
    offset += 7;

    buf[offset++] = 3;
    memcpy(buf + offset, "com", 3);
    offset += 3;

    buf[offset++] = 0;

    buf[offset++] = 0x00;
    buf[offset++] = 0x01;

    buf[offset++] = 0x00;
    buf[offset++] = 0x01;

    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(53)
    };

    inet_pton(AF_INET, "8.8.8.8", &server.sin_addr);

    sendto(fd, buf, offset, 0, (struct sockaddr *)&server, sizeof(server));

    unsigned char response[4096];

    ssize_t n = recvfrom(fd, response, sizeof(response), 0, NULL, NULL);

    dns_header h = decode_header(response);
    print_header(&h);

    close(fd);
}