//使用fcntl函数添加非阻塞
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int flags=fcntl(0,F_GETFL);
    flags=flags|O_NONBLOCK;
    fcntl(0,F_SETFL,flags);
    char buf[32];
    while (1)
    {
        fgets(buf,sizeof(buf),stdin);
        sleep(1);
        printf("buf:%s\n",buf);
    }
    return 0;
}

