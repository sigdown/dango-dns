#ifndef DANGO_CLI_H
#define DANGO_CLI_H

typedef struct {
    const char *domain;
    const char *server;
} resolve_options;

int cli_run(int argc, char **argv);

#endif