#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid_t ret;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {

        sleep(5);
        exit(0);
    }
    else
    {
        while (1)
        {
            ret = waitpid(pid, NULL, WNOHANG); //非阻塞状态
            /*
            waitpid功能：回收进程
            参数：
            第一个
            >0是pid号
            -1任意一个结束得pid号
            第二个
            子进程得结束状态
            第三个参数
            0是阻塞
            WNOHANG非阻塞     
            */
            if (ret == 0)
            {
                puts("时间正在流动");
                sleep(1);
            }
            if (ret == pid)
            {
                puts("OVER");
                exit(0);
            }
        }
    }

    return 0;
}
