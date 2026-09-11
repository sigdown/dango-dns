#ifndef DNS_H
#define DNS_H

#include "buffer.h"
#include <stdint.h>
#include <string.h>

// DNS wire format stuctures

typedef struct {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} dns_header;

typedef struct {
    char qname[256];
    uint16_t qtype;
    uint16_t qclass;
} dns_question;

// parse functions

dns_header decode_header(dango_cur_t* cur);

#endif