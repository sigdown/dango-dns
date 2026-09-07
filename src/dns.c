#include "dns.h"

#include <arpa/inet.h>
#include <netinet/in.h>

static uint16_t read_u16(const uint8_t *b, size_t *offset) {
    uint16_t raw;

    memcpy(&raw, b + *offset, sizeof raw);
    *offset += sizeof raw;

    return htons(raw);
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