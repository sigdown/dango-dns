#include "cli.h"
#include "dns.h"
#include "io.h"
#include "net.h"
#include "query_builder.h"
#include "buffer.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("dango hello v0.1");

    dango_buf_t response_buf = buffer_init(4096);

    int fd = udp_open();

    ssize_t n = udp_fetch(fd, &response_buf);

    if (n < 0)
        exit(1);

    udp_close(fd);

    buffer_free(&response_buf);
    exit(0);
}