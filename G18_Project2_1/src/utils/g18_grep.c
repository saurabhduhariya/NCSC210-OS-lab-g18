/*
 * g18_grep.c - Simplified grep utility for G18 UNIX-like shell project
 *
 * Usage: g18-grep [-i] [-n] [-c] [-v] <pattern> <file...>
 *
 * Flags:
 *   -i  Case-insensitive matching
 *   -n  Print line numbers before matching lines
 *   -c  Print only a count of matching lines
 *   -v  Invert match (print lines that do NOT match)
 */

#include "../../include/common.h"
#include <getopt.h>
#include <ctype.h>

/* ------------------------------------------------------------------ */
/* Helper: convert string to lowercase in-place (for -i flag)         */
/* ------------------------------------------------------------------ */
static void to_lower(char *s) {
    for (; *s; s++) {
        *s = (char)tolower((unsigned char)*s);
    }
}

/* ------------------------------------------------------------------ */
/* Core: search one file for pattern, return number of matching lines  */
/* ------------------------------------------------------------------ */
static int grep_file(FILE *fp, const char *filename,
                     const char *pattern,
                     int flag_i, int flag_n, int flag_c, int flag_v,
                     int multiple_files) {
    char line[4096];
    char line_lower[4096];
    char pattern_lower[1024];
    int  line_num   = 0;
    int  match_count = 0;

    /* Pre-compute lowercase pattern once when -i is active */
    strncpy(pattern_lower, pattern, sizeof(pattern_lower) - 1);
    pattern_lower[sizeof(pattern_lower) - 1] = '\0';
    if (flag_i) {
        to_lower(pattern_lower);
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;

        /* Remove trailing newline for clean output */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        /* Build the string to search in */
        const char *haystack = line;
        if (flag_i) {
            strncpy(line_lower, line, sizeof(line_lower) - 1);
            line_lower[sizeof(line_lower) - 1] = '\0';
            to_lower(line_lower);
            haystack = line_lower;
        }

        int matched = (strstr(haystack, flag_i ? pattern_lower : pattern) != NULL);

        /* Apply invert flag */
        if (flag_v) matched = !matched;

        if (!matched) continue;

        match_count++;

        /* In -c mode we only count, don't print lines yet */
        if (flag_c) continue;

        /* Print: [filename:]  [line_num:]  line */
        if (multiple_files) {
            printf("%s:", filename);
        }
        if (flag_n) {
            printf("%d:", line_num);
        }
        printf("%s\n", line);
    }

    /* In -c mode, print the count after processing the whole file */
    if (flag_c) {
        if (multiple_files) {
            printf("%s:", filename);
        }
        printf("%d\n", match_count);
    }

    return match_count;
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */
int main(int argc, char *argv[]) {
    int opt;
    int flag_i = 0;   /* -i  ignore case          */
    int flag_n = 0;   /* -n  show line numbers     */
    int flag_c = 0;   /* -c  count only            */
    int flag_v = 0;   /* -v  invert match          */

    while ((opt = getopt(argc, argv, "incv")) != -1) {
        switch (opt) {
            case 'i': flag_i = 1; break;
            case 'n': flag_n = 1; break;
            case 'c': flag_c = 1; break;
            case 'v': flag_v = 1; break;
            default:
                fprintf(stderr,
                    "Usage: %s [-i] [-n] [-c] [-v] <pattern> <file...>\n",
                    argv[0]);
                return 1;
        }
    }

    /* After flags we need at least: pattern + one file */
    if (optind + 1 >= argc) {
        fprintf(stderr,
            "Usage: %s [-i] [-n] [-c] [-v] <pattern> <file...>\n",
            argv[0]);
        return 1;
    }

    const char *pattern       = argv[optind];
    int         first_file    = optind + 1;
    int         multiple_files = (argc - first_file) > 1;
    int         total_matches  = 0;
    int         exit_code      = 1;   /* 1 = no match found (grep convention) */

    for (int i = first_file; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror(argv[i]);
            continue;
        }

        int matches = grep_file(fp, argv[i], pattern,
                                flag_i, flag_n, flag_c, flag_v,
                                multiple_files);
        total_matches += matches;
        fclose(fp);
    }

    if (total_matches > 0) {
        exit_code = 0;   /* 0 = at least one match found */
    }

    return exit_code;
}
