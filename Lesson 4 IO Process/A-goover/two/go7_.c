//lseek调用
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int ft;
    ft = open("2.txt",O_WRONLY);
    if (ft<0)
    {
        perror("2.txt");
        return -1;
    }
    lseek(ft,10,SEEK_CUR);
    write(ft,"hello",5);
    close(ft);
    return 0;
}
