//有名管道得创建
//也是使用文件IO
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    if (mkfifo("./fifo", 0666) != 0)
    {
        if (errno == EEXIST)
        {
            printf("no matter");
        }
        else
        {
            perror("mkfifo");
            return -1;
        }
    }
    pid_t tip;
    tip = open("./fifo", O_RDWR);
    if (tip < 0)
    {
        perror("open");
        return -1;
    }

    char arr[10] = "";
    write(tip, "hello", 6);
    read(tip, arr, 6);
    printf("%s",arr);
    return 0;
}
