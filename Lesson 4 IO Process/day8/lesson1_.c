/*
有名和无名管道
pipe //无名管道
mkfifo //有名管道
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char const *argv[])
{
    int tid_fifo;
    int tid_file;
    int a;
    char buf[32] = "";
    if (mkfifo("./fifo", 0666) < 0)
    {
        if (errno == EEXIST)
        {
            printf("YES\n");
        }
        else
        {
            perror("fifo");
            return -1;
        }
    }
    tid_fifo = open("./fifo", O_WRONLY);
    if (tid_fifo == EOF)
    {
        perror("tid_fifo");
        return -1;
    }
    tid_file = open(argv[1], O_RDONLY);
    if (tid_file == EOF)
    {
        perror("open file");
        return -1;
    }

    while (1)
    {
        a = read(tid_file, buf, 32); //最后还是利用了a
        if (a == 0)
        {
            break;
        }
        write(tid_fifo, buf, a);
    }
    exit(0);
    return 0;
}
