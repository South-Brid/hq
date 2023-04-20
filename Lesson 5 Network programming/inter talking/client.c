/***********client****************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void handly(int arg)
{
    waitpid(-1, NULL, WNOHANG);
    exit(0);
}

#define N 128
enum un
{
    login, //登录信息
    chat,  //聊天信息
    exited //离开
};
//链表存储登录得地址和下一个地址
typedef struct node
{
    struct sockaddr_in addr; //
    struct node *next;
} node_t, *node_p;
//存储消息类型，用户名和消息正文
typedef struct msg_t
{
    int type;       //enum un{login,chat,quit};
    char name[32];  //用户名
    char text[128]; //消息正文
} MSG_T, *MSG_P;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("use:fd\n");
        return -1;
    }

    //1.socket创建特殊套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //2.填充结构体
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(atoi(argv[1]));
    client_addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t client_addr_len = sizeof(client_addr);

    //3.进行通信前需创建个人信息
    char buf[128];
    MSG_T user_account_number;
    printf("Please enter your name:");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n')
    {
        buf[strlen(buf) - 1] = '\0';
    }
    strcpy(user_account_number.name, buf);
    //4.输入信息后，向服务器发送登录信息

    user_account_number.type = login;
    ssize_t send_num = sendto(sockfd, &(user_account_number), sizeof(user_account_number),
                              0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (send_num < 0)
    {
        perror("sendto err");
        return -1;
    }

    //5.创建父子进程
    //父进程用来接受
    //子进程用来聊天
    int ret;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
        return -1;
    }
    else if (pid == 0) //子进程用来聊天
    {
        while (1)
        {
            if (strncmp("quite", user_account_number.text, 5) == 0)
            {
                user_account_number.type = exited;
                sendto(sockfd, &user_account_number, sizeof(user_account_number),
                       0, (struct sockaddr *)&client_addr, sizeof(client_addr));
                exit(0);
            }
            fgets(user_account_number.text, sizeof(user_account_number.text), stdin);
            user_account_number.type = chat;
            sendto(sockfd, &user_account_number, sizeof(user_account_number),
                   0, (struct sockaddr *)&client_addr, sizeof(client_addr));
        }
    }
    else
    {
        while (1) //父进程用来接受
        {
            ssize_t recv_num = recvfrom(sockfd, &user_account_number,
                                        sizeof(user_account_number),
                                        0, NULL, NULL);
            if (recv_num < 0)
            {
                perror("recv_num err.");
                return -1;
            }
            //三种状态广播
            if (user_account_number.type == login)
            {
                printf("%s\n", user_account_number.text);
            }
            else if (user_account_number.type == chat)
            {
                sprintf(buf, "%s:%s", user_account_number.name, user_account_number.text);
                printf("%s", buf);
            }
            else if (user_account_number.type == exited)
            {
                printf("%s\n", user_account_number.text);
            }
            signal(SIGCHLD, handly);
        }
    }
    close(sockfd);
    return 0;
}
