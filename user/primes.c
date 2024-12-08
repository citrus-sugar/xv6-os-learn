#include "kernel/types.h"
#include "user/user.h"

int main()
{
    /**
     * 父 - 子1 - 子2
     * 因为 x = p1^a1 * p2^a2 ...
     * 每个进程维护一个质数，每次父进程派出一个数字后，
     * 从左筛到右边，如果没有被筛掉，就是质数
     * 是质数，则另外创建一个进程
     * 
     * 每个进程维持一个质数
     */

    int hold = -1, holdMax = 0;
    int lfd[2];

    pipe(lfd);

    if (fork() == 0)
    {
        // 第一个子进程，维护2
        close(lfd[1]);
        hold = 2, holdMax = 1;

        fprintf(2, "prime %d\n", hold);

        int x = 0;
        int rfd[2];
        while(read(lfd[0], &x, 4) != 0)
        {
            if (x % hold == 0)
                continue;
            if (holdMax) {
                pipe(rfd);
                holdMax = 0;
                if (fork() == 0)
                {
                    hold = x; holdMax = 1;
                    close(lfd[0]); close(rfd[1]);
                    lfd[0] = dup(rfd[0]); close(rfd[0]);

                    fprintf(2, "prime %d\n", hold);

                } else {
                    close(rfd[0]);
                }
            } else {
                write(rfd[1], &x, 4);
            }
        }
        
        if (!holdMax) {
            close(lfd[0]), close(rfd[1]);
            wait(0);
            exit(0);
        } else {
            close(lfd[0]);
            exit(0);
        }
    } else {
        // 父进程
        close(lfd[0]);
        for (int i = 3; i <= 35; i ++)
        {
            write(lfd[1], &i, 4);
        }
        close(lfd[1]); // 链式关闭
        wait(0);
        exit(0);
    }
}