#include "../../include/common.h"

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    int ch;

    if (argc != 3) {
        printf("Usage: g18-cp <source_file> <destination_file>\n");
        return 1;
    }

    src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("Error: cannot open source file\n");
        return 1;
    }

    dest = fopen(argv[2], "w");
    if (dest == NULL) {
        printf("Error: cannot create destination file\n");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    printf("File copied successfully!\n");

    fclose(src);
    fclose(dest);

    return 0;
}
