#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(2, "usage: sleep [n ticks]\n");
        exit(1);
    }

    int nticks = atoi(argv[1]);
    if (nticks < 0) {
        fprintf(2, "ticks can't < 0\n");
    }

    int ret = sleep(nticks);
    exit(ret);
}