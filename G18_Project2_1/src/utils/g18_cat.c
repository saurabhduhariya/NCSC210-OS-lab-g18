#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cat_file(FILE *fp, int show_lines) {
    char buf[4096];
    if (show_lines) {
        int line_num = 1;
        while (fgets(buf, sizeof(buf), fp)) {
            printf("%6d  %s", line_num++, buf);
        }
    } else {
        size_t nread;
        while ((nread = fread(buf, 1, sizeof(buf), fp)) > 0) {
            fwrite(buf, 1, nread, stdout);
        }  }
}
int main(int argc, char *argv[]) {
    int show_lines = 0;
    int arg_start = 1;
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_lines = 1;
        arg_start = 2;
    }
    if (arg_start == argc) {
        cat_file(stdin, show_lines);
    } else {
      for (int i = arg_start; i < argc; i++) {
         FILE *fp = fopen(argv[i], "r");
         if (fp == NULL){
                perror(argv[i]);
                continue;
            }
            cat_file(fp, show_lines);
            fclose(fp);
        }
    }
    return 0;
}
