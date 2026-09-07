#ifndef DNS_H
#define DNS_H

#include <stdint.h>
#include <string.h>

typedef struct {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} dns_header;

typedef struct {
    uint8_t qname[255];
    uint16_t qtype;
    uint16_t qclass;
} dns_question;

typedef struct {
    dns_header header;
    dns_question question;
} dns_query;

dns_header decode_header(const uint8_t *b);
size_t encode_header(const dns_header *h, uint8_t *b);

size_t decode_qname(const uint8_t *buf);

#endif