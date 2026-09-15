#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>

static int cmd_resolve(int argc, char **argv) {
    resolve_options opts = {
        .domain = NULL
    };

    if (argc < 1) {
        fprintf(stderr, "dango resolve: missing domain\n");
        return 1;
    }

    opts.domain = argv[0];

    printf("domain: %s\n", opts.domain);

    return 0;
}

int cli_run(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: dango <command> [options]\n");
        return 1;
    }

    if (strcmp(argv[1], "resolve") == 0) {
        return cmd_resolve(argc - 2, argv + 2);
    }

    fprintf(stderr, "dango: unknown command '%s'\n", argv[1]);
    return 1;
}