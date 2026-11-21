#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define ENTRY_MAX 8

void find(char *path, char *target)
{
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, O_RDONLY)) < 0) {
        return;
    }

    if (fstat(fd, &st) < 0) {
        close(fd);
        return;
    }

    if (st.type != T_DIR) {
        close(fd);
        return;
    }

    char entries[ENTRY_MAX][DIRSIZ]; // relative location from `path`
    int cnt = 0;
    char buf[512];
    strcpy(buf, path);
    char *cur = buf + strlen(buf);
    *cur++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        memmove(cur, de.name, DIRSIZ);
        if (strcmp(cur, ".") == 0 || strcmp(cur, "..") == 0)
            continue;
        if (strcmp(cur, target) == 0)
            printf("%s\n", buf);
        cur[DIRSIZ] = 0;
        if (stat(buf, &st) < 0)
            continue;
        if (st.type == T_DIR) {
            strcpy(entries[cnt++], cur);
        }

        if (cnt == ENTRY_MAX)
        {
            for (int i = 0; i < cnt; i++) {
                strcpy(cur, entries[i]);
                find(buf, target);
            }
            
            cnt = 0;
        }
    }
    close(fd);

    for (int i = 0; i < cnt; i++) {
        strcpy(cur, entries[i]);
        find(buf, target);
    }

    return;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("usage: find {root path} {file name}\n");
        return 0;
    }

    char *root = argv[1];
    char *fileName = argv[2];
 
    find(root, fileName);

    return 0;
}