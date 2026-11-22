#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>

#define PATH_MAX 4096

const char *get_category(const char *filename) {
    const char *dot = strrchr(filename, '.');
    
    if (!dot || dot == filename) {
        return "Other";
    }

    if (strcasecmp(dot, ".txt") == 0 || 
        strcasecmp(dot, ".md") == 0 || 
        strcasecmp(dot, ".docx") == 0) {
        return "Documents";
    }
    if (strcasecmp(dot, ".c") == 0 || 
        strcasecmp(dot, ".h") == 0 || 
        strcasecmp(dot, ".go") == 0) {
        return "Sources";
    }
    if (strcasecmp(dot, ".jpg") == 0 || 
        strcasecmp(dot, ".png") == 0) {
        return "Images";
    }
    if (strcasecmp(dot, ".pdf") == 0) {
        return "PDFs";
    }

    return "Other";
}

int ensure_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0755) != 0 && errno != EEXIST) {
             printf("Помилка створення директорії\n -- %s\n", path);
            return -1;
        }
    }
    return 0;
}

int copy_file(const char *src_path, const char *dst_path) {
    FILE *src = fopen(src_path, "rb");
    if (!src) {
        printf("Помилка шляху Source. Директорія існує?");
        return -1;
    }

    FILE *dst = fopen(dst_path, "wb");
    if (!dst) {
        printf("Помилка шляху Destination. Директорія існує?");
        fclose(src);
        return -1;
    }

    char buffer[8192];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dst) != bytes) {
            printf("Помилка запису");
            fclose(src);
            fclose(dst);
            return -1;
        }
    }

    fclose(src);
    fclose(dst);
    return 0;
}


void process_directory(const char *src_dir, const char *out_dir, FILE *logFile) {
    DIR *dir = opendir(src_dir);
    if (!dir) {
        printf("Не вдалося відкрити директорію\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        char full_src_path[PATH_MAX];
        snprintf(full_src_path, sizeof(full_src_path), "%s/%s", src_dir, entry->d_name);

        struct stat st;
        if (lstat(full_src_path, &st) != 0) {
            printf("lstat failed");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            char real_src[PATH_MAX], real_out[PATH_MAX];
            if (realpath(full_src_path, real_src) && realpath(out_dir, real_out)) {
                if (strcmp(real_src, real_out) == 0) {
                    continue;
                }
            }
            process_directory(full_src_path, out_dir, logFile);
        } else if (S_ISREG(st.st_mode)) {
            const char *category = get_category(entry->d_name);

            char category_dir[PATH_MAX];
            snprintf(category_dir, sizeof(category_dir), "%s/%s", out_dir, category);
            if (ensure_dir(category_dir) != 0) {
                continue;
            }

            char full_dst_path[PATH_MAX];
            snprintf(full_dst_path, sizeof(full_dst_path), "%s/%s", category_dir, entry->d_name);

            fprintf(logFile, "> %s -> %s\n", full_src_path, full_dst_path);
            printf("> %s -> %s\n", full_src_path, full_dst_path);
           
            copy_file(full_src_path, full_dst_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Використання: sorter path/to/source path/to/out\n");
        return 1;
    }

    const char *src_dir = argv[1];
    const char *out_dir = argv[2];

    if (ensure_dir(out_dir) != 0) {
        return 1;
    }
    char *log_path = strdup(out_dir);
    strcat(log_path, "/sort_result.log");
    FILE *fd = fopen(log_path, "w");
    process_directory(src_dir, out_dir, fd);
    fclose(fd);
    printf("Історія сортування записана в лог: %s\n", log_path);
    return 0;
}
