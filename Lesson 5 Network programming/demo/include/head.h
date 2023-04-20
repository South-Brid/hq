#ifndef _HEAD_H_
#define _HEAD_H_
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define N 128 //name
#define M 128 //listen

enum un
{
    REGISTER, //注册
    LOGIN,    //登录
    QUERY,    //查询
    HISTORY   //历史记录
};

typedef struct
{
    int type;              //功能类型
    char name[N];          //用户名
    char data[256];        //密码
    char information[256]; //消息标志
    char word[256];        //查询得单词
    char explain[256];     //单词解释
} MSG_T, *MSG_P;

//客户端界面函数
void PrintfShow();
//客户端注册函数
int client_do_register(int fd, MSG_T* msg);
//客户端口登录函数
int client_do_login(int fd, MSG_T* msg);
//客户端二级界面函数
void printf_next_show();
//客户端二级流程函数
int dictionary_process(int fd, MSG_T* msg);
//查询函数
int client_do_query(int fd, MSG_T *msg);
//历史记录函数
int client_do_history(int fd, MSG_T* msg);



//服务器函数
void handly(int arg);
//注册检测添加函数
int server_do_register(int fd, MSG_T msg, sqlite3 *db, char *errmsg);
//服务器端登录
int server_do_login(int fd, MSG_T msg, sqlite3 *db, char *errmsg);
//服务器查询功能
int server_do_query(int fd, MSG_T msg, sqlite3 *db, char *errmsg);
//回调函数
int callback(void *arg, int f_num, char **f_val, char **f_name);
//历史记录函数
//需要用到回调函数进行
int server_do_history(int fd, MSG_T msg, sqlite3 *db, char *errmsg);

#endif