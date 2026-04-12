#include "../../include/common.h"
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes
#define COLOR_DIR     "\x1b[1;34m"
#define COLOR_RESET   "\x1b[0m"

void print_long_format(const char *path, const char *filename) {
    struct stat st;
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, filename);

    if (lstat(full_path, &st) == -1) { // lstat handles symlinks better
        perror("stat");
        return;
    }

    // Permissions logic
    printf((S_ISDIR(st.st_mode)) ? "d" : (S_ISLNK(st.st_mode) ? "l" : "-"));
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");

    // Owner and Group
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);
    char *owner = pw ? pw->pw_name : "unknown";
    char *group = gr ? gr->gr_name : "unknown";

    // Time Formatting
    char time_buf[20];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", tm_info);

    // Color Logic for filename
    const char *color = S_ISDIR(st.st_mode) ? COLOR_DIR : "";
    
    printf(" %2ld %-8s %-8s %8ld %s %s%s%s\n", 
           st.st_nlink, owner, group, st.st_size, time_buf, color, filename, COLOR_RESET);
}

int main(int argc, char *argv[]) {
    int opt;
    int flag_a = 0;
    int flag_l = 0;

    while ((opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a': flag_a = 1; break;
            case 'l': flag_l = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-al] [directory]\n", argv[0]);
                return 1;
        }
    }
    
    char *target_dir = (optind < argc) ? argv[optind] : ".";

    // Using scandir to get a sorted list of files
    struct dirent **namelist;
    int n = scandir(target_dir, &namelist, NULL, alphasort);

    if (n < 0) {
        fprintf(stderr, "ls: cannot access '%s': %s\n", target_dir, strerror(errno));
        return 1;
    }

    for (int i = 0; i < n; i++) {
        struct dirent *entry = namelist[i];

        // Skip hidden files if -a is not set
        if (!flag_a && entry->d_name[0] == '.') {
            free(namelist[i]);
            continue;
        }

        if (flag_l) {
            print_long_format(target_dir, entry->d_name);
        } else {
            // Add color to standard view
            struct stat st;
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", target_dir, entry->d_name);
            stat(full_path, &st);
            
            if (S_ISDIR(st.st_mode)) 
                printf(COLOR_DIR "%s  " COLOR_RESET, entry->d_name);
            else 
                printf("%s  ", entry->d_name);
        }
        free(namelist[i]);
    }
    
    if (!flag_l) printf("\n");

    free(namelist);
    return 0;
}