#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    FILE *fp;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        setsid();
        chdir("/tmp");//注意点
        umask(0);
        for (int i = 0; i < 3; i++)
        {
            close(i);
        }
        fp = fopen("2.txt", "w");
        if (fp == NULL)
        {
            perror("err");
            exit(0);
        }
        while (1)
        {
            fputs("hello\n", fp);
            fflush(fp);
           // sleep(1);
        }
    }
    else
    {
        exit(0);
    }
    return 0;
}
