#include "cli.h"

#include <bits/getopt_core.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint16_t parse_qtype(const char *s)
{
    if (strcmp(s, "A") == 0) {
        return 1;
    }

    if (strcmp(s, "AAAA") == 0) {
        return 28;
    }

    fprintf(stderr, "unknown type: %s\n", s);
    exit(EXIT_FAILURE);
}

cli_options parse_cli(int argc, char **argv) {
    cli_options opts = {
        .cmd = RESOLVE,
        .domain = NULL,
        .server = "1.1.1.1",
        .qtype = 1,
    };

    if (argc < 2) {
        fprintf(stderr, "usage: %s [resolve|trace|probe] <domain> [options]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int arg_start = 1;

    if (strcmp(argv[1], "resolve") == 0) {
        opts.cmd = RESOLVE;
        arg_start = 2;
    } else if (strcmp(argv[1], "trace") == 0) {
        opts.cmd = TRACE;
        arg_start = 2;
    } else if (strcmp(argv[1], "probe") == 0) {
        opts.cmd = PROBE;
        arg_start = 2;
    } else {
        opts.cmd = RESOLVE;
        arg_start = 1;
    }

    optind = arg_start;

    static struct option long_options[] = {
        {"server", required_argument, NULL, 's'},
        {"type", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0},
    };

    int c;

    while ((c = getopt_long(argc, argv, "s:t:", long_options, NULL)) != -1) {
        switch (c) {
        case 's':
            opts.server = optarg;
            break;

        case 't':
            opts.qtype = parse_qtype(optarg);
            break;

        default:
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "domain required\n");
        exit(EXIT_FAILURE);
    }

    opts.domain = argv[optind];

    return opts;
}