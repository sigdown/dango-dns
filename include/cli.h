#ifndef CLI_H
#define CLI_H

#include <stdint.h>

typedef enum {
    RESOLVE,
    TRACE,
    PROBE
} command;

typedef struct {
    command cmd;
    const char *domain;
    const char *server;
    uint16_t qtype;
} cli_options;

cli_options parse_cli(int argc, char **argv);

#endif