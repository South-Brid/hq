//无名管道特性问题
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fd[2] = {};
    char arr[10] = "";
    if (pipe(fd) != 0)
    {
        perror("pipe");
        return -1;
    }
    #if 0
    write(fd[1], "hello", 6);
    read(fd[0], arr, 6);
    printf("%s\n", arr);
    read(fd[0],arr,6);
    printf("hello\n");//管道中没有东西，读阻塞
    close(fd[1]);
    read(fd[0],arr,10);
    printf("hehe\n");
    #endif
    close(fd[0]);//将读端关闭，对管道里面写东西，会导致管道破裂
    write(fd[1],arr,100);
    printf("aiaiaiai\n");
    
    return 0;
}
