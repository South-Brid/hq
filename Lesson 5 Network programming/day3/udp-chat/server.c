// 引入所需头文件
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 创建UDP数据包套接字
    if (sockfd < 0)                              // 如果创建失败则打印错误信息并退出程序
    {
        perror("socket err");
        return -1;
    }
    struct sockaddr_in saddr, caddr;       // 创建两个IPV4套接字地址结构体
    saddr.sin_family = AF_INET;            // 设置地址族为IPV4
    saddr.sin_port = htons(atoi(argv[1])); // 设置端口号为第一个命令行参数
    saddr.sin_addr.s_addr = INADDR_ANY;    // 设置本地IP地址为任意地址
    socklen_t len = sizeof(caddr);         // 计算地址结构体的大小

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) // 绑定套接字到指定地址和端口
    {
        perror("bind err"); // 如果绑定失败，则打印错误信息并退出程序
        return -1;
    }
    char buf[128]; // 创建一个缓冲区用于存放接收到的消息
    while (1)      // 进入循环，不断接收数据包并输出
    {
        if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&caddr, &len) < 0) // 接收数据包
        {
            perror("recvfrom err"); // 如果接收失败，则打印错误信息并退出程序
            return -1;
        }
        printf("端口号：%d\n", ntohs(caddr.sin_port)); // 输出发送端口号
        printf("ip：%s\n", inet_ntoa(caddr.sin_addr)); // 输出发送者IP地址
        printf("%s", buf);                             // 输出消息内容
    }
    return 0;
}
