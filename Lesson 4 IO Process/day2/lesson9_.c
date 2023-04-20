#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fd;
    int fw;
    char arr[100];
    /*
    利用argc和argv得特性给用户提示
     */
    if (argc != 3)
    {
        printf("usef:%s <oldname> <newname>", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR); //可读可写
    if (fd < 0)
    {
        perror("fist error");
        return -1;
    }
    fw = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, 0666);
    //可读可写 清除2.txt，让他每次都重新复制
    if (fw < 0)
    {
        perror("next error");
        return -1;
    }
    ssize_t x = 0;
    while (x = read(fd, arr, 10)) //利用read结束返回零得特性 把fd读到arr
    {
        write(fw, arr, x); //将arr中得写到fw
    }
    close(fd);
    close(fw);
    return 0;
}
