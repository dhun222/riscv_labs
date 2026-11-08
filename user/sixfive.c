#include "kernel/types.h"
#include "user/user.h"

int findSeperator(char c)
{
    const char seperators[] = " -\r\t\n./,";
    int i = 0;
    while (seperators[i] != '\0') {
        if (c == seperators[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

void sixfive() 
{
    char buf[512];
    buf[0] = '-';
    while (gets(buf + 1, sizeof(char) * 512)) {
        if (buf[1] == '\0') {
            break;
        }
        int i = 0;
        while (buf[i] != '\0' || i < 512) {
            if (!findSeperator(buf[i])) {
                i++;
                continue;
            }
            i++;
            int t = 0;
            char candidate[512];
            while ('0' <= buf[i] && buf[i] <= '9') {
                candidate[t] = buf[i];
                i++; t++;
            }
            if (t) {
                candidate[t] = '\0';
                int number = atoi(candidate);
                if (number % 5 == 0 || number % 6 == 0) {
                    printf("%d\n", number);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        sixfive();
        exit(0);
    }

    close(0);
    for (int k = 1; k < argc; k++) {
        if (open(argv[k], 0)) {
            printf("sixfive: cannot open %s\n", argv[k]);
            continue;
        }

        sixfive();
        close(0);
    }

    exit(0);
}
