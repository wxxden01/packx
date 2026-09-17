#include <unistd.h>
#include <stdio.h>

int sudo() {
    if (geteuid() != 0) {
        return -1;
    }

    return 0;
}   