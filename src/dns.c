#include "dns.h"
#include "buffer.h"

#include <arpa/inet.h>
#include <netinet/in.h>

dns_header decode_header(dango_cur_t *cur) {
    dns_header h;

    if (!read_u16(cur, &h.id)) return 
}

/*
for example - qname(ya.ru) -> 02 79 61 02 72 75 00
02 means next two are 79 (y) and 61 (a).
02 means next two are 72 (r) and 75(ru)
00 is the end of the sequence
*/
