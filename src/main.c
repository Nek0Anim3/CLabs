#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int isDotDir(char *name) {
    if (name[0] != '.' || (name[0] != '.' && name[1] != '.')) {
         return 0;
    } else {
         return 1;
    }
}

int file_count = 0;
int dir_count = 0;

void printTree(const char *base_path, const char *prefix) {
    DIR *dir = opendir(base_path);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
         if (!isDotDir(entry->d_name)) {
            count++;
        }
    }

    rewinddir(dir);
    int current = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (isDotDir(entry->d_name)) {
            continue;
        }
        current++;
        int isLast = (current == count);
        printf("%s%s%s\n", prefix, isLast ? "└── " : "├── ", entry->d_name);

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
        struct stat statbuf;
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            char new_prefix[1024];
            dir_count++; 
            snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, isLast ? "    " : "│   ");
            printTree(path, new_prefix);
        } else {
            file_count++;
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    char currentDir[1024];
    getcwd(currentDir, sizeof(currentDir));
    const char *target_dir = (argc > 1) ? argv[1] : currentDir;
    printf("%s\n", target_dir);
    printTree(target_dir, "");
    printf("Files: %d | Folders: %d\n", file_count, dir_count);
    return 0;
}
