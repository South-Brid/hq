//使用有名管到实现两个互不干涉得文件复制
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid_fifo;
    pid_t pid_file;
    char buf[32]="";
    ssize_t a;
    if (mkfifo("./fifo", 0666) < 0)
    {
        if (errno == EEXIST)
        {
            printf("ok\n");
        }
        else
        {
            perror("mkfifo");
            return -1;
        }
    }
    pid_fifo = open("./fifo", O_WRONLY);
    if (pid_fifo < 0)
    {
        perror("pid_fifo");
        return -1;
    }
    pid_file = open(argv[1], O_RDONLY);
    if (pid_fifo < 0)
    {
        perror("pid_file");
        return -1;
    }
    while (1)
    {
        a=read(pid_file,buf,32);
        write(pid_fifo,buf,a);
        if (a == 0)
        {
            break;
        }
    }
    return 0;
}
