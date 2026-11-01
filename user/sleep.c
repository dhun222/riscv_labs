#include "kernel/types.h"
#include "user/user.h"

int main (int argc, char *argv[])
{
    int seconds = 0;
    if (argc != 2 ||'0' > *argv[1] || *argv[1] > '9' || (seconds = atoi(argv[1])) < 0 ) {
        printf("Usage: sleep <seconds>\n");
        return 0;
    }

    pause(seconds);
    return 0;
}