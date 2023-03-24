#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void find_largest_files (const char *file_path, off_t *maxWSize, char *maxFSize, off_t *max_nonw_size, char *max_nonw_file, off_t *disc_usage){
    DIR *dir = opendir(file_path);
    if(!dir){
        perror("Error opening directory");
        return;
    }

    struct dirent *file_entry;
    while ((file_entry = readdir(dir)) != NULL){
        if(strcmp(file_entry->d_name, ".") == 0 || strcmp(file_entry->d_name, "..") == 0){
            continue;
        }
        char file_buff[500];
        sprintf(file_buff, "%s/%s", file_path, file_entry->d_name);

        struct stat stat_file;
        if(stat(file_buff, &stat_file) == -1){
            perror("stat");
            continue;
        }

        if(S_ISREG(stat_file.st_mode)){
            int writable_file = access(file_buff, W_OK) == 0;
            if(writable_file){
                if(stat_file.st_size > *maxWSize){
                    *maxWSize = stat_file.st_size;
                    strcpy(maxFSize, file_entry -> d_name);
                }
            }
            else{
                if(stat_file.st_size > *max_nonw_size){
                    *max_nonw_size = stat_file.st_size;
                    strcpy(max_nonw_file, file_entry->d_name);
                }
            }
            *disc_usage += stat_file.st_size;
        }
        else if(S_ISDIR(stat_file.st_mode)){
            find_largest_files(file_buff, maxWSize, maxFSize, max_nonw_size, max_nonw_file, disc_usage);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1; 
    }
    off_t maxWSize = 0, max_nonw_size = 0, disc_usage = 0;
    char maxFSize[500] = "", max_nonw_file[500] = "";

    find_largest_files(argv[1], &maxWSize, maxFSize, &max_nonw_size, max_nonw_file, &disc_usage);

    printf("Largest writable file: %s (%jd bytes)\n", maxFSize, (long) maxWSize);
    printf("Largest non-writable file: %s (%jd bytes)\n", max_nonw_file, (long) max_nonw_size);
    printf("Total disk usage: %jd bytes\n", disc_usage);
}


