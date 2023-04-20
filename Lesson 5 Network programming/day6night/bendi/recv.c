#include <netinet/in.h>
#include <string.h>
#include <sys/un.h>
#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char const *argv[])
{
    int socked = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socked < 0)
    {
        perror("socked err.");
        return -1;
    }
    struct sockaddr_un saddr, caddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sun_family = AF_UNIX;
    strcpy(saddr.sun_path, "./mutex");

    bind(socked,(struct sockaddr *)&saddr,sizeof(saddr));

    
    accept(socked)

    while (1)
    {
        
    }
    

    return 0;
}
