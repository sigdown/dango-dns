#include "dns.h"
#include "buffer.h"
#include "net.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

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

static int form_header(dango_buf_t *out) {
    memcpy(out->data, query, 29);
}

int form_request(char *domain, uint16_t type, dango_buf_t *out) {
    
}

// parse functions

int parse_header(dango_cur_t *cur, dns_header *hdr) {
    if (!read_u16(cur, &hdr->id)) return -1;
    if (!read_u16(cur, &hdr->flags)) return -1;
    if (!read_u16(cur, &hdr->qdcount)) return -1;
    if (!read_u16(cur, &hdr->ancount)) return -1;
    if (!read_u16(cur, &hdr->nscount)) return -1;

    return 0;
}

int parse_question(dango_cur_t *cur, dns_question *qst) {
    dango_buf_t *buf = cur->buf;
    uint8_t *qname = qst->qname;

    while(buf->data[cur->pos] != 0) {
        if(!read_u8(cur,qname)) return -1;
        qname += 1;
    }

    if (!read_u8(cur, qname)) return -1;
    if (!read_u16(cur, &qst->qtype)) return -1;
    if (!read_u16(cur, &qst->qclass)) return -1;

    return 0;
}

//dns functions

int dns_resolve(const char *ip, uint16_t type) {
    dango_buf_t request_buffer = buffer_init(512);
    dango_buf_t response_buffer = buffer_init(2048);

    dango_cur_t request_cursor = from_buf(&request_buffer);
    dango_cur_t response_cursor = from_buf(&response_buffer);

    int fd = udp_open();
}

/*
for example - qname(ya.ru) -> 02 79 61 02 72 75 00
02 means next two are 79 (y) and 61 (a).
02 means next two are 72 (r) and 75(ru)
00 is the end of the sequence
*/
