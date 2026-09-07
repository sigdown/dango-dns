#ifndef QUERY_BUILDER_H
#define QUERY_BUILDER_H

#include "cli.h"

#include <stdint.h>
#include <sys/types.h>

ssize_t build_resolve_request(uint8_t *b, size_t size, cli_options *opts);

#endif