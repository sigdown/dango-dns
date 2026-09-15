#ifndef DANGO_CLI_H
#define DANGO_CLI_H

typedef struct {
    const char *domain;
} resolve_options;

int cli_run(int argc, char **argv);

#endif