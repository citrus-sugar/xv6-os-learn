#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    // argv 最后一定要有个null或nullptr或0，不然可能会出问题
    char buf[512], *xargv[MAXARG], *p, *pend, *pst;
    int n;

    // printf("argc: %d\n", argc);
    for (int i = 1; i < argc; i ++)
        xargv[i - 1] = argv[i];
    
    p = buf;
    while ((n = read(0, p, sizeof(buf) - (p - buf))) > 0)
        p = p + n;

    pend = p;
    p = pst = buf;
    while (p < pend)
    {
        while (*p != '\n')
            p ++;
        *p++ = 0;
        xargv[argc - 1] = pst;
        xargv[argc] = 0;
        pst = p;

        // for (int i = 0; i <= argc; i ++)
        //     printf("%s ", xargv[i]);
        // printf("\n");

        if (fork() == 0) {
            exec(xargv[0], xargv);
            exit(0);
        } else {
            wait(0);
        }
    }
    exit(0);
}