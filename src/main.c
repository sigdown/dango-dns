#include "cli.h"
#include "dns.h"
#include "io.h"
#include "net.h"
#include "query_builder.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char **argv) {
    uint8_t domain[7] = { 0x02,  0x79, 0x62, 0x02, 0x72, 0x75, 0x00 };
    char string[7];

    parse_qname(string, domain);

    printf("%s", string);

    printf("dango v0.1!\n");

    cli_options opts = parse_cli(argc, argv);

    size_t request_len = 0;

    uint8_t request[4096];
    uint8_t response[4096];

    switch (opts.cmd) {
        case RESOLVE:
            request_len = build_resolve_request(
                request, 
                sizeof request, 
                &opts
            );
            break;

        case TRACE:
            fprintf(stderr, "trace: not implemented\n");
            exit(-1);
            break;

        case PROBE:
            fprintf(stderr, "probe: not implemented\n");
            exit(-1);
            break;
    }

    printf("dango: ok\n\n");

    int fd = open_udp();

    dns_header h = decode_header(request);

    print_header(&h);

    send_udp(fd, opts.server, 53, request, request_len);

    fetch_udp(fd, response, sizeof response);

    printf("\n");

    h = decode_header(response);

    print_header(&h);

    exit(close_udp(fd));
}