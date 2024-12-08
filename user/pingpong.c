#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int pfd[2], cfd[2];
    char buf[] = {0xFA};

    pipe(pfd), pipe(cfd);

    if (fork() == 0) {
        // 只开启 父读 子写
        close(pfd[1]);
        close(cfd[0]);
        if (read(pfd[0], buf, sizeof buf) <= 0) {
            // ...
        } else {
            fprintf(2, "%d: received ping\n", getpid());
        }
        close(pfd[0]);
        if (write(cfd[1], buf, 1) != 1) {
            // ...
        }
        exit(0);
    } else {
        close(pfd[0]);
        close(cfd[1]);
        if (write(pfd[1], buf, sizeof buf) != 1) {
            // ...
        }
        close(pfd[1]);
        if (read(cfd[0], buf, sizeof buf) <= 0) { // 阻塞，不需要wait
            // ...
        } else {
            fprintf(2, "%d: received pong\n", getpid());
        }
        close(cfd[0]);
        exit(0);
    }
}