//使用有名管到实现两个互不干涉得文件复制
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t fid_fifo;
    pid_t fid_file;
    char arr[32]="";
    ssize_t a;
    if (mkfifo("./fifo", 0666) < 0)
    {
        if (errno == EEXIST)
        {
            printf("2ok\n");
        }
        else
        {
            perror("mkfifo err");
            return -1;
        }
    }
    fid_fifo=open("./fifo",O_RDONLY);
    if (fid_fifo<0)
    {
        perror("fifo");
        return -1;
    }
    fid_file=open(argv[1],O_CREAT|O_WRONLY|O_TRUNC,0666);
    if (fid_file<0)
    {
        perror("file");
        return -1;
    }
    while (1)
    {
       a=read(fid_fifo,arr,32);
       write(fid_file,arr,a);
       if (a == 0)
       {
           break;
       }
    }
    close(fid_file);
    close(fid_fifo);
    return 0;
}
