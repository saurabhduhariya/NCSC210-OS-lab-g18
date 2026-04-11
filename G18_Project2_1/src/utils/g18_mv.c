#include "../../include/common.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) == -1) {
        perror("g18-mv error");
        return 1;
    }

    printf("Moved/Renamed '%s' to '%s' successfully.\n", argv[1], argv[2]);
    return 0;
}