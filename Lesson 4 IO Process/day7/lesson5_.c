/* 
管道得特性
1.管道内部没有数据得时候，读管道阻塞
2.管道内部数据满（65536），写阻塞，除非有4k空间才能写入，4096
3.管道内部没有数据得时候，将写段fd[1]关闭,读操作直接返回
4.将读端关闭fd[0],进行写操作会导致管道破裂
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 30
int main(int argc, char const *argv[])
{
    char arr[N] = "";
    int fd[2] = {0};
    if (pipe(fd) < 0)
    {
        perror("pipe erro");
        return -1;
    }
    int pid;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        while (1)
        {
            //sleep(1);
            read(fd[0], arr, N);
            if (strcmp(arr, "quite") == 0)
            {
                break;
            }
            printf("%s\n", arr);
        }
    }
    else
    {

        while (1)
        {
            scanf("%s", arr);
            write(fd[1], arr, strlen(arr)+1);
            if (strcmp(arr, "quite") == 0)
            {
                break;
            }
        }
        wait(NULL);//这是对得
    }

    return 0;
}
