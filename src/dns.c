#include "dns.h"
#include "buffer.h"

#include <arpa/inet.h>
#include <netinet/in.h>

int decode_header(dango_cur_t *cur, dns_header *hdr) {
    if (!read_u16(cur, &hdr->id)) return -1;
    if (!read_u16(cur, &hdr->flags)) return -1;
    if (!read_u16(cur, &hdr->qdcount)) return -1;
    if (!read_u16(cur, &hdr->ancount)) return -1;
    if (!read_u16(cur, &hdr->nscount)) return -1;

    return -1;
}

/*
for example - qname(ya.ru) -> 02 79 61 02 72 75 00
02 means next two are 79 (y) and 61 (a).
02 means next two are 72 (r) and 75(ru)
00 is the end of the sequence
*/
