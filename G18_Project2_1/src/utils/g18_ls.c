#include "../../include/common.h"
#include <dirent.h>
#include <errno.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

void print_long_format(const char *path,const char *filename){
    struct stat st;
    char full_path[1024];
    snprintf(full_path,sizeof(full_path),"%s/%s",path,filename);
    if(stat(full_path,&st)==-1){
        perror("stat");
        return;
    }
    printf((S_ISDIR(st.st_mode))?"d":"-");
    printf((st.st_mode & S_IRUSR)?"r":"-");
    printf((st.st_mode & S_IWUSR)?"w":"-");
    printf((st.st_mode & S_IXUSR)?"x":"-");

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr=getgrgid(st.st_gid);

    char time_buf[20];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(time_buf,sizeof(time_buf),"%b %d %H:%M",tm_info);

    printf(" %2ld %-8s %-8s %8ld %s %s\n",st.st_nlink, pw->pw_name, gr->gr_name, st.st_size, time_buf, filename);
}

int main(int argc, char *argv[]) {
    int opt;
    int flag_a=0;
    int flag_l=0;

    while((opt=getopt(argc, argv, "al"))!=-1){
        switch(opt){
            case 'a':flag_a = 1; break;
            case 'l': flag_l = 1; break;
            default:
                fprintf(stderr,"Usage: %s [-al] [directory]\n", argv[0]);
                return 1;
        }
    }
    char *target_dir=(optind<argc)?argv[optind] : ".";

    DIR *dir_ptr = opendir(target_dir);

    if (dir_ptr == NULL) {
        fprintf(stderr, "ls: cannot access '%s': %s\n", target_dir, strerror(errno));
        return 1;
    }

    // 3. Read entries one by one
    struct dirent *entry;
    
    // readdir returns NULL when there are no more files
    while ((entry = readdir(dir_ptr)) != NULL) {
        
        if (!flag_a && entry->d_name[0] == '.') continue;

        if (flag_l) {
            print_long_format(target_dir, entry->d_name);
        } else {
            printf("%s  ", entry->d_name);
        }
    }

    if (!flag_l) printf("\n");

    // 4. Close the directory
    closedir(dir_ptr);

    return 0;
}