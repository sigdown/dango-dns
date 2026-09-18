#include "cli.h"
#include "dns.h"
#include "io.h"
#include "net.h"
#include "buffer.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char **argv) {
    return cli_run(argc, argv);
}