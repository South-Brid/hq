#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
int fd;
void handly(int arg)
{
    char buf[32];
    int ret = read(fd, buf, sizeof(buf));
    buf[ret] = '\0';
    printf("%s\n", buf);
}

int main(int argc, char const *argv[])
{
    fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open err.");
        return -1;
    }
    fcntl(fd,F_SETOWN, getpid());
    int flags = fcntl(fd, F_GETFL);
    flags = flags | O_ASYNC;
    fcntl(fd, F_SETFL, flags);
    signal(SIGIO, handly);
    while (1)
    {
        printf("hello\n");
        sleep(1);
    }

    return 0;
}
