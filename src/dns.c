#include "dns.h"
#include "buffer.h"

#include <arpa/inet.h>
#include <netinet/in.h>

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

/*
for example - qname(ya.ru) -> 02 79 61 02 72 75 00
02 means next two are 79 (y) and 61 (a).
02 means next two are 72 (r) and 75(ru)
00 is the end of the sequence
*/
