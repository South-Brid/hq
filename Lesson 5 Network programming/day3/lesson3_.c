#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    //打开鼠标
    int fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    char buf[32];
    while (1)
    {
        //键盘
        fgets(buf, 32, stdin);
        printf("key:%s\n", buf);
        
        //鼠标
        int ch = read(fd, buf, sizeof(buf));
        buf[ch] = '\0';
        printf("mouse:%s\n", buf);
    }
    close(fd);
    return 0;
}
