#include<stdio.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<dirent.h>
#include<sys/stat.h>

enum type_t
{
    login, //登录信息
    chat,  //聊天信息
    exited //离开
};
typedef struct msg_t
{
    int type;       //enum un{login,chat,quit};
    char name[32];  //用户名
    char text[128]; //消息正文
} MSG_T, *MSG_P;


int main(int argc, char const *argv[])
{
   
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
    {
        perror("socket err");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(atoi(argv[1]));
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    socklen_t len = sizeof(serveraddr);
    MSG_T msg;
    //先执行登录操作 
    printf("请登录:\n");
    msg.type=login;
    printf("请输入用户名:");
    fgets(msg.name,32,stdin);
    if(msg.name[strlen(msg.name)-1]=='\n')
       msg.name[strlen(msg.name)-1]='\0';
    //发送登录消息
    if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,len)<0)
       {
         perror("sendto err");
         exit(-1);
       }
    pid_t pid=fork();
     if(pid<0)
    {
        perror("fork err");
        exit(-1);
    }
    else if(pid==0)
    {
        while(1)
        {
            if(recvfrom(sockfd,&msg,sizeof(msg),0,NULL,NULL)<0)
            {
                perror("recvfrom err");
                return -1;
            }
            printf("[%s]:%s\n",msg.name,msg.text);
        } 
    }    
    else 
    {
        while(1)
        {
            fgets(msg.text,sizeof(msg.text),stdin);
            if(msg.text[strlen(msg.text)-1]=='\n')
               msg.text[strlen(msg.text)-1]='\0';
            if(strcmp(msg.text,"quit")==0)
            {
                msg.type=exited; 
                sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,len);
                kill(pid,SIGKILL);
                wait(NULL);
                exit(-1);
            }else
        {
            msg.type=chat;
        }
        //发送消息
        sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,len);
        }
    }
    close(sockfd);
    return 0;
}
