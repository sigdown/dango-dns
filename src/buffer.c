#include "buffer.h"
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