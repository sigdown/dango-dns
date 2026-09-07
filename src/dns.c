#include "dns.h"

#include <arpa/inet.h>
#include <netinet/in.h>

static uint16_t read_u16(const uint8_t *b, size_t *offset) {
    uint16_t raw;

    memcpy(&raw, b + *offset, sizeof raw);
    *offset += sizeof raw;

    return ntohs(raw);
}

static void write_u16(uint8_t *b, size_t *offset, uint16_t value) {
    uint16_t raw = htons(value);

    memcpy(b + *offset, &raw, sizeof raw);
    *offset += sizeof raw;
}

dns_header decode_header(const uint8_t *b) {
    dns_header h = {0};
    
    size_t offset = 0;

    h.id = read_u16(b, &offset);
    h.flags = read_u16(b, &offset);
    h.qdcount = read_u16(b,&offset);
    h.ancount = read_u16(b, &offset);
    h.nscount = read_u16(b, &offset);
    h.arcount = read_u16(b, &offset);

    return h;
}

size_t encode_header(const dns_header *h, uint8_t *b) {
    size_t offset = 0;

    write_u16(b, &offset, h->id);
    write_u16(b, &offset, h->flags);
    write_u16(b, &offset, h->qdcount);
    write_u16(b, &offset, h->ancount);
    write_u16(b, &offset, h->nscount);
    write_u16(b, &offset, h->arcount);

    return offset;
}

dns_question decode_question(const uint8_t *b) {
    dns_question q = {0};

    parse_qname(q.qname, b);
}

size_t parse_qname(char *a, const uint8_t *b) {
    size_t i = 0;
    size_t out_i = 0;

    while (b[i] != 0) {
        size_t len = b[i];

        for (size_t j = 0; j < len; j++) {
            a[out_i] = (char)b[i + 1 + j];
            out_i++;
        }

        i += 1 + len;

        if (b[i] != 0) {
            a[out_i] = '.';
            out_i++;
        }
    }

    a[out_i] = '\0';

    return i;
}

/*
for example - qname(ya.ru) -> 02 79 61 02 72 75 00
02 means next two are 79 (y) and 61 (a).
02 means next two are 72 (r) and 75(ru)
00 is the end of the sequence
*/
