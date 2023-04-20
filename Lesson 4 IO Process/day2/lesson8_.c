#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fd;
    char arr[10] = {0};
    fd = open("8.txt", O_RDWR);
    /*
    程序创建得文件最后得权限是0664,是因为有umask得存在，umask得值是0002
    最终权限是输入得权限&(~umask)
    */
    if (fd < 0)
    {
        perror("8.txt");
        return -1;
    }
    printf("%d\n", fd);
    ssize_t x = read(fd, arr, 10); //函数得返回类型是ssize_t类型
    /*
    第一个参数是文件描述符
    第二个是读取文件到到得数组
    第三个是数据个数
     */
    write(fd, arr, x);
    printf("%s", arr);
    close(fd);
    return 0;
}