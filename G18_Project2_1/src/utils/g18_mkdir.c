#include "../../include/common.h"
#include <errno.h>
#include <getopt.h>
#include <limits.h>

static int mkdir_p(const char *path) {
    char tmp[PATH_MAX];
    size_t len = strlen(path);

    if (len == 0 || len >= sizeof(tmp)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    strcpy(tmp, path);

    // Trim trailing slash so we don't try to create an empty final segment.
    if (len > 1 && tmp[len - 1] == '/') {
        tmp[len - 1] = '\0';
    }

    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, 0777) == -1 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, 0777) == -1 && errno != EEXIST) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int create_parents = 0;

    while ((opt = getopt(argc, argv, "p")) != -1) {
        switch (opt) {
            case 'p':
                create_parents = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] directory...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-p] directory...\n", argv[0]);
        return 1;
    }

    int exit_code = 0;
    for (int i = optind; i < argc; i++) {
        int rc = create_parents ? mkdir_p(argv[i]) : mkdir(argv[i], 0777);
        if (rc == -1) {
            perror(argv[i]);
            exit_code = 1;
        }
    }

    return exit_code;
}
