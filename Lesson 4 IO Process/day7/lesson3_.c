/*
无名管道
 */
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fd[2] = {0};
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return -1;
    }
    char arr[10]="";
    write(fd[1],"arr",6);
    read(fd[0],arr,6);
    printf("%s",arr);
    printf("%s","hello");
    return 0;
}
