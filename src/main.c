#include "cli.h"
#include "net.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char **argv) {

    printf("dango v0.1!\n");

    cli_options opts = parse_cli(argc, argv);

    size_t request_len = 0;

    switch (opts.cmd) {
        case RESOLVE:
            printf("resolve");
            break;
            
        case TRACE:
            fprintf(stderr, "trace: not implemented\n");
            break;

        case PROBE:
            fprintf(stderr, "probe: not implemented\n");
            break;
    }

    printf("dango: ok\n");

    int fd = open_udp();

    uint8_t request[4096];
    uint8_t response[4096];

    send_udp(fd, "1.1.1.1", 53, request, 29);

    fetch_udp(fd, response, sizeof response);

    exit(close_udp(fd));
}

/*
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

    close(fd);*/