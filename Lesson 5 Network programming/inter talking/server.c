/***********server****************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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

//创建有头单向链表
node_p linklist_create(void);
//遍历链表发送消息
int radio_broadcast(int sockfd, node_p p, MSG_T msg, struct sockaddr_in client_addr);
//用户聊天
int user_chat(int sockfd, MSG_T msg, node_p p, struct sockaddr_in client_addr);
//用户退出
int user_exit(int sockfd, MSG_T msg, node_p p, struct sockaddr_in client_addr);

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
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    socklen_t client_addr_len = sizeof(client_addr);

    //3.绑定
    int bind_val = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &bind_val, sizeof(bind_val));
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind err.");
        return -1;
    }

    //4.创建聊天室
    node_p chat_room = linklist_create();
    int ret;
    MSG_T msg;
    while (1)
    {
        //链接客户端
        ret = recvfrom(sockfd, &msg, sizeof(msg),
                       0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (ret < 0)
        {
            perror("revfrom err.");
            return -1;
        }

        if (msg.type == login) //功能1：用户登录打印登录信息
        {
            strcpy(msg.text, "加入队伍");
            printf("port:%d ip:%s name:%s %s\n", ntohs(client_addr.sin_port),
                   inet_ntoa(client_addr.sin_addr), msg.name, msg.text);

            int radio_val = radio_broadcast(sockfd, chat_room, msg, client_addr);
            if (radio_val != 1)
            {
                printf("radio_broadcast err.\n");
            }
        }
        else if (msg.type == chat)
        {
            int user_val = user_chat(sockfd, msg, chat_room, client_addr);
            if (user_val != 1)
            {
                printf("user_chat is err.\n");
                return -1;
            }
        }
        else if (msg.type == exited)
        {
            user_exit(sockfd, msg, chat_room, client_addr);
        }
    }
    close(sockfd);
    return 0;
}

//用户退出
int user_exit(int sockfd, MSG_T msg, node_p p, struct sockaddr_in client_addr)
{

    node_p pdel = NULL;
    sprintf(msg.text, "%s战略性撤退了", msg.name);
    puts(msg.text);
    while (p->next != NULL)
    {
        if (memcmp(&(p->next->addr), &client_addr, sizeof(client_addr)) == 0) //相等进行删除操作,找到要删除得节点前一位
        {
            pdel = p->next;
            p->next = pdel->next;
            free(pdel);
            pdel = NULL;
        }
        else
        {
            p = p->next;
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&(p->addr),sizeof(p->addr)); //传输退出信息给所有客户端
        }
    }
}

//用户聊天
int user_chat(int sockfd, MSG_T msg, node_p p, struct sockaddr_in client_addr)
{
    while (p->next != NULL)
    {
        p = p->next;
        if (memcmp(&(p->addr), &client_addr, sizeof(client_addr)) != 0) //使用将存储区里面得内容进行比较
        //检查该节点的地址信息是否与发送方的地址信息相同。如果不相同，则将消息发送到该节点的地址。
        {
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&p->addr, sizeof(p->addr));
        }
    }
    return 1;
}

//遍历链表发送消息
int radio_broadcast(int sockfd, node_p p, MSG_T msg, struct sockaddr_in client_addr)
{
    node_p pnew = (node_p)malloc(sizeof(node_t));
    sprintf(msg.text, "%s 加入队伍", msg.name);
    while (p->next != NULL) //遍历链表给所有成员发送登录消息
    {
        p = p->next;
        sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&p->addr, sizeof(p->addr));
    }
    pnew->addr = client_addr;
    pnew->next = NULL;
    p->next = pnew;
    return 1;
}

//创建有头单向链表
node_p linklist_create(void)
{
    node_p p = (node_p)malloc(sizeof(node_t));
    if (p == NULL)
    {
        printf("malloc is err.\n");
        return NULL;
    }
    p->next = NULL;
    return p;
}