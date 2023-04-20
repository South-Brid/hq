#include "head.h"

int main(int argc, char const *argv[])
{
    MSG_T msg;
    if (argc != 2)
    {
        puts("Please use the program name and port number");
        return -1;
    }
    //打开用户注册数据库user.db
    sqlite3 *db = NULL;
    char *errmsg = NULL;
    if (sqlite3_open("./user.db", &db) != SQLITE_OK)
    {
        fprintf(stderr, "sqlite3_open user.db err:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    //创建数据库表user
    if (sqlite3_exec(db, "create table user(name char primary key,passwd char);",
                     NULL, NULL, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "create_table  user err:%s\n", errmsg);
    }
    printf("create table user ok\n");
    //创建数据库表history
    if (sqlite3_exec(db, "create table history(name char,time char,word char);",
                     NULL, NULL, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "create_table history err:%s\n", errmsg);
    }
    printf("create table history ok\n");

    //创建流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //填充结构体
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;

    socklen_t caddr_len = sizeof(caddr);

    //忘记绑定了
    bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    //监听
    if (listen(sockfd, M) < 0)
    {
        perror("listen err.");
        return -1;
    }
    while (1)
    {
        //循环接受
        int accepfd = accept(sockfd, (struct sockaddr *)&caddr, &caddr_len);
        if (accepfd < 0)
        {
            perror("accept err.");
            return -1;
        }
        signal(SIGCHLD, handly);
        //创建子进程
        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return -1;
        }
        else if (pid == 0) //子进程进行通信
        {
            while (1)
            {
                //接受客户端发来得消息
                recv(accepfd, &msg, sizeof(msg), 0);
                switch (msg.type)
                {
                case REGISTER: //注册
                    server_do_register(accepfd, msg, db, errmsg);
                    break;
                case LOGIN: //登录
                    server_do_login(accepfd, msg, db, errmsg);
                    break;
                case QUERY: //查询单词
                    server_do_query(accepfd, msg, db, errmsg);
                    break;
                case HISTORY://历史记录
                    server_do_history(accepfd, msg, db, errmsg);
                    break;
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
