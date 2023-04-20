#include "head.h"

int main(int argc, char const *argv[])
{
    int chose_num;
    MSG_T msg;
    //用户提示
    if (argc != 2)
    {
        puts("Please use the program name and port number");
        return -1;
    }

    //创建流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //设置端口重复使用
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //填充结构体
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(atoi(argv[1]));
    caddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&caddr, sizeof(caddr)) < 0)
    {
        perror("connect err.");
        return -1;
    }
    while (1)
    {
        PrintfShow();
        scanf("%d", &chose_num);
        switch (chose_num)
        {
        case 1:
            client_do_register(sockfd, &msg);
            break;
        case 2:
            if (client_do_login(sockfd, &msg) == 1)
            {
                if (dictionary_process(sockfd, &msg) == 1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        case 3:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}