//无名管道得验证
#include<unistd.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
    int fd[2]={0};
    if(pipe(fd)<0)
    {
        perror("pipe err");
        return -1;
    }
    char arr[70000]="";
    write(fd[1],arr,65536);
    printf("hello\n");
    read(fd[0],arr,4095);
    write(fd[1],"a",1);
    printf("world\n");
    return 0;
}
