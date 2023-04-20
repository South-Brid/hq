#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    //kill(getpid(),SIGKILL);
    raise(9);
    alarm(5);
    printf("hello world\n");
    alarm(3);
    printf("welcome new world\n");
    pause();
    return 0;
}
