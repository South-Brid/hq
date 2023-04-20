#include "head.h"

//客户端二级流程函数
int dictionary_process(int fd, MSG_T *msg)
{
    int chose_next;
    while (1)
    {
        printf_next_show();
        scanf("%d", &chose_next);
        switch (chose_next)
        {
        case 1:
            client_do_query(fd, msg);
            break;
        case 2:
            client_do_history(fd, msg);
            break;
        case 3:
            return 1;
        default:
            break;
        }
    }
    return 0;
}
//历史记录函数
int client_do_history(int fd, MSG_T *msg)
{
    msg->type = HISTORY;
    send(fd, msg, sizeof(MSG_T), 0);
    memset(msg, 0, sizeof(MSG_T));//这里出现问题
    while (1)
    {
        if (strncmp(msg->information, "end_of\0", 8) == 0)
        {
            return 1;
        }
        recv(fd, msg, sizeof(*msg), 0);
        printf("%s\n", msg->information);
    }
    return 0;
}

//查询函数
int client_do_query(int fd, MSG_T *msg)
{
    msg->type = QUERY;
    while (1)
    {
        printf("Please enter the word you want to query:");
        scanf("%s", msg->word);
        if (strncmp("#", msg->word, 1) == 0)
        {
            break;
        }
        send(fd, msg, sizeof(*msg), 0);
        recv(fd, msg, sizeof(*msg), 0);
        if (strncmp(msg->information, "find\0", 6) == 0)
        {
            printf("%s\n", msg->explain);
        }
        else
        {
            printf("not find\n");
        }
    }
}

//客户端二级界面函数
void printf_next_show()
{
    puts("词典界面");
    printf("*******************************************\n");
    printf("*1:qyery_word   2.history_record   3.quite*\n");
    printf("*******************************************\n");
    printf("****************by sqt*********************\n");
    printf("please choose:");
}

//客户端口登录函数
int client_do_login(int fd, MSG_T *msg)
{
    //登录函数
    msg->type = LOGIN;
    puts("登录界面"); //标记一下
    puts("Please enter username:");
    scanf("%s", msg->name);
    puts("Please enter password:");
    scanf("%s", msg->data);
    send(fd, msg, sizeof(*msg), 0);
    recv(fd, msg, sizeof(*msg), 0);
    puts(msg->information);
    if (strncmp(msg->information, "Login successful\0", 18) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//客户端注册函数
int client_do_register(int fd, MSG_T *msg)
{
    msg->type = REGISTER;
    puts("注册界面"); //标记一下
    puts("Please enter username:");
    scanf("%s", msg->name);
    puts("Please enter password:");
    scanf("%s", msg->data);
    //发送注册信息给服务器
    send(fd, msg, sizeof(*msg), 0);
    recv(fd, msg, sizeof(*msg), 0); //接受服务器消息提示是否成功
    printf("register:%s\n", msg->information);
    return 0;
}

//客户端一级界面函数
void PrintfShow()
{
    puts("注册界面");
    printf("*******************************************\n");
    printf("********1:register 2:login 3:quite*********\n");
    printf("*******************************************\n");
    printf("****************by sqt*********************\n");
    printf("please choose:");
}
