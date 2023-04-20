#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char buf[32];
    int flags = fcntl(0, F_GETFL);
    flags = flags | O_NONBLOCK;
    
    fcntl(0, F_SETFL, flags); //奇怪
    /*
    int flags = fcntl(0,F_GETFL);
    flags=flags|O_NONBLOCK;
    fcntl(0,F_SETFL,flags);
    */
    while (1)
    {
        fgets(buf, 32, stdin);
        sleep(1);
        printf("buf:%s\n", buf);
    }
    return 0;
}
