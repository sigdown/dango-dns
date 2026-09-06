#include "io.h"

#include <stdio.h>

static void print_flags(const uint16_t flags) {
    printf("qr: %d ", flags >> 15);
    printf("opcode: %d ", (flags >> 11) & 0xf);
    printf("aa: %d ", (flags >> 10) & 0x1);
    printf("tc: %d ", (flags >> 9) & 0x1);
    printf("rd: %d ", (flags >> 8) & 0x1);
    printf("ra: %d ", (flags >> 7) & 0x1);
    printf("z: %d ", (flags >> 4) & 0x7);
    printf("rcode: %d\n", flags & 0xf);
}

void print_header(const dns_header *h) {
    uint16_t flags = h->flags;
    
    printf("id: 0x%X\n", h->id);

    print_flags(flags);

    printf("qdcount: %d\n", h->qdcount);
    printf("ancount: %d\n", h->ancount);
    printf("nscount: %d\n", h->nscount);
    printf("arcount: %d\n", h->arcount);
}

/*
for example f = 0x8180
in binary: 1000 0001 1000 0000
format: 1|0000|0|0|1|1|000|0000
qr = flags >> 15 -> 0000 0000 0000 0001
opcode = (flags >> 11) & 0xf -> 0x0000 ok
...
*/