#include "query_builder.h"
#include "dns.h"
#include <sys/types.h>
#include <unistd.h>

ssize_t build_resolve_request(uint8_t *b, size_t size, cli_options *opts) {
    if (size < 12) {
        return -1;
    }

    size_t offset = 0;

    dns_header h = {
        .id = 0x1234,
        .flags = 0x0100,
        .qdcount = 1,
        .ancount = 0,
        .nscount = 0,
        .arcount = 0
    };

    offset += encode_header(&h, b + offset);

    return (ssize_t)offset;
}

