#include "cli.h"
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

int main(int argc, char **argv) {
    return cli_run(argc, argv);
}