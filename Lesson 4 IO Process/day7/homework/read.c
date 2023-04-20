#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    //1.创建管道路
    if (mkfifo("./fifo", 0666) < 0)
    {
        if (errno == EEXIST)
        {
            printf("mkfifo ok\n");
        }
        else
        {
            perror("mkfifo");
            return -1;
        }
    }
    //2.打开管道文件
    pid_t pid;
    pid = open("./fifo", O_WRONLY);//只写打开，写阻塞
    if (pid < 0)
    {
        perror("open dir");
        return -1;
    }
    //3.打开目标文件
    pid_t pid2;
    pid2 = open(argv[1], O_RDONLY);
    if (pid2 < 0)
    {
        perror("open dir");
        return -1;
    }
    //（1）进行循环将pid2文件里内容写入arr
    //（2）然后将arr里面得内容读到pid管道中
    char arr[20] = "";
    int ch = 0;
    while ((ch = read(pid2, arr, 20)) != 0)//将文件读到arr
    {
        write(pid, arr, ch);//arr写到管道，但是因为管道只写打开，会被阻塞
    }
    close(pid);
    return 0;
}
