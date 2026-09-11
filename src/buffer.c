#include "buffer.h"
#include <stdlib.h>

dango_buf_t* buffer_init(size_t init_cap) {
    dango_buf_t *buf;

    buf->data = malloc(init_cap);
    buf->len = 0;
    buf->cap = init_cap;

    return buf;
}

void buffer_free(dango_buf_t *buf) {
    free(buf->data);
    buf->data = NULL;
    buf->len = 0;
    buf->cap = 0;
}