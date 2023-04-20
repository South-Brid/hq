#include <stdio.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

void list_server(int acceptfd, char *buf, int size);
void put_server(int acceptfd, char *buf, int size);
void get_server(int acceptfd, char *buf, int size);
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input %s <port>\n", argv[0]);
        return -1;
    }
    //1.创建流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //链接
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd:%d\n", sockfd); //3
    //填充ipv4的通信结构体

    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1])); //"8888" int a= atoi("8888")//a=8888
    //saddr.sin_addr.s_addr = inet_addr(argv[1]);

    //设置服务器自动获取自己主机的ip
    // saddr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY  0x00000000 "0.0.0.0"
    // saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    socklen_t len = sizeof(caddr);

    //2.绑定套接字 ip和端口(自己)
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok.\n");

    //3.监听
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok.\n");
    /************************调用select***********************************/

    //1.创建
    fd_set readfds, tmpfds;
    //2.qing
    FD_ZERO(&readfds);
    //3.tian
    FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);
    int mutex = sockfd;
    int ret;
    char buf[32];
    while (1)
    {
        tmpfds = readfds;
        ret = select(mutex + 1, &tmpfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        //判断动作
        if (FD_ISSET(0, &tmpfds))
        {
            fgets(buf, sizeof(buf), stdin);
            printf("key:%s\n", buf);
        }
        if (FD_ISSET(sockfd, &tmpfds))
        {
            int acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
            if (acceptfd < 0)
            {
                perror("accept err.");
                return -1;
            }
            printf("acceptfd=%d\n", acceptfd); //通信
            printf("client:ip=%s port=%d\n",
                   inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
        }
    }
    close(sockfd);
    return 0;
}
// //3、get
// void get_server(int acceptfd, char *buf, int size) //buf->put xxx.c
// {
//     //1>打开文件 读
//     int fd = open(buf + 4, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open file err.");
//         return;
//     }
//     int ret; //实际读到的个数
//     while ((ret = read(fd, buf, size - 1)) != 0)
//     {
//         buf[ret] = '\0';
//         send(acceptfd, buf, size, 0);
//     }
//     strcpy(buf, "get ok.");
//     send(acceptfd, buf, size, 0);
// }
// //2.接收文件(本地：打开新建文件接收客户端发送过来的内容写到文件)
// void put_server(int acceptfd, char *buf, int size)
// {
//     int fd = open(buf + 4, O_TRUNC | O_CREAT | O_WRONLY, 0666);
//     if (fd < 0)
//     {
//         perror("open err.");
//         return;
//     }
//     while (1)
//     {
//         if (recv(acceptfd, buf, size, 0) < 0)
//         {
//             perror("recv err.");
//             return;
//         }
//         if (strncmp(buf, "put ok.", 7) == 0)
//             break;
//         write(fd, buf, strlen(buf));
//     }
// }

// //list：打开当前目录读文件判断文件是普通文件将文件名传给客户端
// void list_server(int acceptfd, char *buf, int size)
// {
//     //1.打开当前目录文件
//     DIR *dir = opendir("./");
//     if (dir == NULL)
//     {
//         perror("opendir err.");
//         return;
//     }
//     //2.循环读目录文件  readdir
//     struct dirent *dp = NULL;
//     struct stat st;
//     while ((dp = readdir(dir)) != NULL)
//     {
//         //dp->d_name拿到的文件名
//         //判断文件属性stat
//         stat(dp->d_name, &st);
//         if (S_ISREG(st.st_mode))
//         {
//             strcpy(buf, dp->d_name);
//             send(acceptfd, buf, size, 0);
//         }
//     }
//     //发送结束标志
//     strcpy(buf, "list ok.");
//     send(acceptfd, buf, size, 0);
// }