#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("use:fd\n");
        return -1;
    }
    //1.socket
    int socked = socket(AF_INET, SOCK_STREAM, 0);
    if (socked < 0)
    {
        perror("socket err.");
        return -1;
    }
    //2.tianchong
    struct sockaddr_in listen_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(atoi(argv[1]));
    listen_addr.sin_addr.s_addr = INADDR_ANY;

    int con_val = connect(socked, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    if (con_val < 0)
    {
        perror("con_val err.");
        return -1;
    }
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
    }
    else if (pid == 0)
    {
        char buf[128];
        ssize_t ret;
        while (1)
        {
            ret = recv(socked, buf, sizeof(buf), 0);
            if (ret < 0)
            {
                perror("recv err");
                return -1;
            }
            else if (ret == 0)
            {
                printf("server is exit\n");
                break;
            }
            else
            {
                printf("%s\n", buf);
            }
        }
    }
    else
    {
        char buf[128];
        while (1)
        {
            fgets(buf, sizeof(buf), stdin);
            if (buf[strlen(buf) - 1] == '\n')
            {
                buf[strlen(buf) - 1] = '\0';
            }
            send(socked, buf, sizeof(buf), 0);//这里
        }
    }
    return 0;
}
