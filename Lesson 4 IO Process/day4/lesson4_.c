//创建守护进程
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        //2.子进程创建新回话,让子进程成为会话组组长
        setsid();
        //3.修改当前路径为根路径
        chdir("/");
        //4.修改文件权限码
        umask(0);
        //5.关闭文件描述符
        for (int i = 0; i < 3; i++)
        {
            close(i);
        }
        while(1);
    }
    else
    {
        //1.让父进程结束
         exit(0);
    }
    return 0;
}
