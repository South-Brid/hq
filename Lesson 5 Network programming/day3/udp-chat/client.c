// 引入所需头文件
#include <stdio.h>
#include <netinet/in.h>
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
if (sockfd < 0) // 如果创建失败则打印错误信息并退出程序
{
perror("socket err");
return -1;
}
struct sockaddr_in saddr; // 创建一个IPV4套接字地址结构体
saddr.sin_family = AF_INET; // 设置地址族为IPV4
saddr.sin_port = htons(atoi(argv[1])); // 设置端口号为第一个命令行参数
saddr.sin_addr.s_addr = inet_addr(argv[2]); // 设置目标IP地址为第二个命令行参数
socklen_t len = sizeof(saddr); // 计算地址结构体的大小
char buf[128]; // 创建一个缓冲区用于存放发送的消息
while (1) // 进入循环，不断读取用户输入并发送数据包
{
fgets(buf, sizeof(buf), stdin); // 从标准输入中读取一行文本
if (buf[strlen(buf) - 1] == '\n') // 如果最后一位是换行符，将其替换为结束符
{
buf[strlen(buf) - 1] == '\0';
}
if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&saddr, len) < 0) // 发送数据包
{
perror("recvfrom err"); // 如果发送失败，则打印错误信息并退出程序
return -1;
}
}
return 0;
}