#ifndef DNS_H
#define DNS_H

#include <stdint.h>

typedef struct {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} dns_header;

typedef struct {
    uint8_t *qname;
    uint16_t qtype;
    uint16_t qclass;
} question;

dns_header decode_header(uint8_t *b);

#endif