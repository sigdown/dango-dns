#include "dns.h"
#include "io.h"
#include "net.h"
#include "buffer.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

uint8_t query[] = {
    0x12, 0x34,             // transaction ID
    0x01, 0x00,             // flags: standard query
    0x00, 0x01,             // 1 question
    0x00, 0x00,             // answers
    0x00, 0x00,             // authority
    0x00, 0x00,             // additional

    0x07, 'e','x','a','m','p','l','e',
    0x03, 'c','o','m',
    0x00,                   // end of name

    0x00, 0x01,             // A
    0x00, 0x01              // IN
};

void print_buffer_hex(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", buf[i]); 
    }
    printf("\n");
}

int main(void) {
    printf("dango hello v0.1\n");

    dango_buf_t response_buf = buffer_init(512);
    dango_buf_t request_buf = buffer_init(512);

    dango_cur_t response_cur = from_buf(&response_buf);

    memcpy(request_buf.data, query, 29);
    request_buf.len = 29;

    int fd = udp_open();

    ssize_t n = udp_send(fd, "8.8.8.8", 53, &request_buf);

    n = udp_fetch(fd, &response_buf);

    if (n < 0)
        exit(1);

    udp_close(fd);

    print_buffer_hex(response_buf.data, response_buf.len);

    dns_header h;

    decode_header(&response_cur, &h);

    print_header(&h);

    printf("%d", response_cur.pos);

    buffer_free(&response_buf);
    buffer_free(&response_buf);

    exit(0);
}