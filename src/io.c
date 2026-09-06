#include "io.h"

#include <stdio.h>

void print_header(dns_header *h) {
    printf("id: 0x%X\n", h->id);
}