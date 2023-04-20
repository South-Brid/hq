//有名管道//也是文件IO
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    char arr[10] = "";
    if (mkfifo("./fifo", 0666) < 0) //errno//创建了一个有名管道
    {
        if (errno == EEXIST)
        {
            printf("ok\n");
        }
        else
        {
            perror("fifo");
            return -1;
        }
    }
    int pid;
    pid = open("./fifo",O_RDWR);
    if (pid == EOF)
    {
        perror("pid");
        return -1;
    }
    write(pid, "haha", 5);
    // read(pid, arr, 5);
    // printf("%s", arr);
    return 0;
}

