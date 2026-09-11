#include "buffer.h"
#include <stdint.h>
#include <stdlib.h>

// buffer

dango_buf_t buffer_init(size_t init_cap) {
    dango_buf_t buf;

    buf.data = malloc(init_cap);
    buf.len = 0;
    buf.cap = init_cap;

    return buf;
}

void buffer_free(dango_buf_t *buf) {
    free(buf->data);
    buf->data = NULL;
    buf->len = 0;
    buf->cap = 0;
}

size_t buffer_remaining(const dango_buf_t *buf) {
    return buf->cap - buf->len;
}

void buffer_clear(dango_buf_t *buf) {
    for (size_t i = 0; i < buf->len; ++i) {
        buf->data[i] = 0;
    }

    buf->len = 0;
}

// cursor

dango_cur_t from_buf(dango_buf_t *buf) {
    dango_cur_t cur; 

    cur.buf = buf;
    cur.pos = 0;

    return cur;
}

bool read_u8(dango_cur_t *cur, uint8_t *out) {
    dango_buf_t *buf = cur->buf;

    if (cur->pos + 1 > buf->len)
        return false;

    *out = buf->data[cur->pos];
    cur->pos += 1;

    return true;
}

bool read_u16(dango_cur_t *cur, uint16_t *out) {
    dango_buf_t *buf = cur->buf;

    if (cur->pos + 2 > buf->len)
        return false;

    *out = ((uint16_t)buf->data[cur->pos] << 8) |
            buf->data[cur->pos + 1];

    cur->pos += 2;

    return out;
}

bool read_u32(dango_cur_t *cur, uint32_t *out) {
    dango_buf_t *buf = cur->buf;

    if (cur->pos + 4 > buf->len)
        return false;

    *out = ((uint32_t)buf->data[cur->pos] << 24) | 
        ((uint32_t)buf->data[cur->pos + 1] << 16) | 
        ((uint32_t)buf->data[cur->pos + 2] << 8) | 
        buf->data[cur->pos];
    
    cur->pos += 4;

    return true;
}