#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *data;
    size_t len;
    size_t cap;
} dango_buf_t;

typedef struct {
    dango_buf_t *buf;
    size_t pos;
} dango_cur_t;

// buffer
dango_buf_t buffer_init(size_t init_cap);
void buffer_free(dango_buf_t *buf);

size_t buffer_remaining(const dango_buf_t *buf);
void buffer_clear(dango_buf_t *buf);

// cursor
dango_cur_t from_buf(dango_buf_t *buf);

#endif