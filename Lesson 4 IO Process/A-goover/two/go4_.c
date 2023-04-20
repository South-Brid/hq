//使用文件IO实现文件CP功能
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    char arr[10];
    int ch;
    int ft;
    int fp;
    if (argc != 3)
    {
        printf("please use :%s <newname> <cpname>\n", argv[0]);
        return -1;
    }
    ft = open(argv[1], O_RDONLY);
    if (ft < 0) //open失败返回-1
    {
        perror(argv[1]);
        return -1;
    }
    fp = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fp < 0) //open失败返回-1
    {
        perror(argv[2]);
        return -1;
    }
    while ((ch = read(ft, arr, 10))) //读取到文件末尾，返回0
    {                                
        write(fp, arr, ch);         //返回读取字符的个数
    }
    close(fp);
    close(ft);
    return 0;
}
