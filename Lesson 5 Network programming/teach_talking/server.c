#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "head.h"

typedef struct node_t
{
    struct sockaddr_in addr;
    struct node_t *next;
} list_t;

list_t *createList(void);
void server_login(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr);
void server_chat(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr);
void server_quit(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr);
int main(int argc, char const *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    socklen_t len = sizeof(caddr);

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    MSG_t msg;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
        return -1;
    }
    else if (pid == 0)
    {
        //创建一个空的链表
        list_t *p = createList();
        while (1)
        {
            if (recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&caddr, &len) < 0)
            {
                perror("recvfrom err.");
                return -1;
            }
            switch (msg.type)
            {
            case login:
                server_login(sockfd, p, msg, caddr);
                break;
            case chat:
                server_chat(sockfd, p, msg, caddr);
                break;
            case quit:
                server_quit(sockfd, p, msg, caddr);
                break;
            }
        }
    }else{
        while(1)
        {
            msg.type=chat;
            strcpy(msg.name,"server");
            fgets(msg.text, sizeof(msg.text), stdin);
            if (msg.text[strlen(msg.text) - 1] == '\n')
                msg.text[strlen(msg.text) - 1] = '\0';
            sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, sizeof(saddr));
        }
    }
    close(sockfd);
    return 0;
}
//quit:
//1.将谁退出消息转发给所有登录的客户端
//2.将推出客户端信息从链表中清除
void server_quit(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr)
{
    list_t *pdel = NULL;
    sprintf(msg.text, "%s quit", msg.name);
    while (p->next != NULL)
    {
        if (memcmp(&(p->next->addr), &caddr, sizeof(caddr)) == 0)
        {
            pdel = p->next;
            p->next = pdel->next;
            free(pdel);
            pdel = NULL;
        }
        else
        {
            p = p->next;
            sendto(sockfd, &msg, sizeof(msg), 0,
                   (struct sockaddr *)&(p->addr), sizeof(p->addr));
        }
    }
}
//chat:
//1.将聊天转发除自己之外的所有客户端(sockfd,p,msg,caddr)
void server_chat(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr)
{
    //遍历链表转发消息
    while (p->next != NULL)
    {
        p = p->next;
        if (memcmp(&(p->addr), &caddr, sizeof(caddr)) == 0)
            continue;
        sendto(sockfd, &msg, sizeof(msg), 0,
               (struct sockaddr *)&(p->addr), sizeof(p->addr));
    }
}
//login：
//1.将谁登录转发所有已经登录的客户端  (链表、sockfd,msg)
//2.将新登录的客户端信息新建节点插入链表 (caddr)
void server_login(int sockfd, list_t *p, MSG_t msg, struct sockaddr_in caddr)
{
    sprintf(msg.text, "%s login", msg.name);
    while (p->next != NULL)
    {
        p = p->next;
        sendto(sockfd, &msg, sizeof(msg), 0,
               (struct sockaddr *)&(p->addr), sizeof(p->addr));
    }
    //创建新节点
    list_t *pnew = (list_t *)malloc(sizeof(list_t));
    pnew->addr = caddr;
    pnew->next = NULL;

    //链接到链表最后
    p->next = pnew;
}

//创建一个空的有头单向链表
list_t *createList(void)
{
    list_t *p = (list_t *)malloc(sizeof(list_t));
    if (NULL == p)
    {
        perror("malloc err.");
        return NULL;
    }
    //初始化节点
    p->next = NULL;
    return p;
}
