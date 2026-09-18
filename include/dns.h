#ifndef DNS_H
#define DNS_H

#include "buffer.h"
#include <stdint.h>

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
    uint8_t qname[256];
    uint16_t qtype;
    uint16_t qclass;
} dns_question;

typedef struct {
    dns_header header;
    dns_question *question;
} dns_message;

int form_request(char *domain, uint16_t type, dango_buf_t *buf);

// parse functions

int parse_header(dango_cur_t *cur, dns_header *hdr);
int parse_question(dango_cur_t *cur, dns_question *qst);

// dns functions

int dns_resolve(const char *ip, uint16_t type);

#endif