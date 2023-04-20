//read函数再攻略
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int ft;
    int fp;
    char arr[10];
    ssize_t ch;
    ft = open(argv[1], O_RDONLY);
    if (ft < 0)
    {
        perror(argv[1]);
        return -1;
    }
    fp = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fp < 0)
    {
        perror(argv[2]);
        return -1;
    }
    while ((ch = read(ft, arr, 10)))
    {
        write(fp,arr,ch);
    }
    return 0;
}