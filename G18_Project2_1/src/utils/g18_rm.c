#include "../../include/common.h"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    int recursive = 0;

    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch (opt) {
            case 'r':
                recursive = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-r] file...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "g18-rm: missing operand\n");
        return 1;
    }

    for (int i = optind; i < argc; i++) {
        if (unlink(argv[i]) == -1) {
            if (recursive && rmdir(argv[i]) == 0) {
                continue;
            }
            perror(argv[i]);
        }
    }

    return 0;
}