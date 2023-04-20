#include "head.h"
//消灭僵尸进程
void handly(int arg)
{
    waitpid(-1, NULL, WNOHANG);
}
//服务器端登录
int server_do_login(int fd, MSG_T msg, sqlite3 *db, char *errmsg)
{
    char **pazresult = NULL; //存放得二维数组
    int pnow;                //结果集中得行数
    int pncolumn;            //结果集中得行数

    msg.type = LOGIN;
    char sql[128];
    sprintf(sql, "select * from user where name=\"%s\" and passwd=\"%s\";", msg.name, msg.data);
    if (sqlite3_get_table(db, sql, &pazresult, &pnow, &pncolumn, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "get_table err:%s", errmsg);
        return -1;
    }
    if (pnow == 0) //行数为0,说明输入得用户名和密码不统一
    {
        strcpy(msg.information, "Your username or password is incorrect\0");
        send(fd, &msg, sizeof(msg), 0);
    }
    else
    {

        strcpy(msg.information, "Login successful\0");
        send(fd, &msg, sizeof(msg), 0);
    }
}

//服务器注册检测添加函数
int server_do_register(int fd, MSG_T msg, sqlite3 *db, char *errmsg)
{
    msg.type = REGISTER;
    char sql[128];
    //将名字和密码语句拼接到sql当中
    sprintf(sql, "insert into user values(\"%s\",\"%s\");", msg.name, msg.data);
    //检测拼接成果
    printf("test1:%s\n", sql);

    if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) == SQLITE_OK)
    {
        strncpy(msg.information, "success\0", 8);
        send(fd, &msg, sizeof(msg), 0);
    }
    else
    {
        strncpy(msg.information, "false\0", 6);
        send(fd, &msg, sizeof(msg), 0);
    }
    return 0;
}
//服务器查询功能
int server_do_query(int fd, MSG_T msg, sqlite3 *db, char *errmsg)
{
    printf("名字测试：%s\n", msg.name);
    int found = 0;
    FILE *file_fd;
    file_fd = fopen("./dict.txt", "r");
    if (file_fd == NULL)
    {
        perror("fopen err.");
        return -1;
    }
    puts("打开词典成功");
    char buf[128];
    // puts("****************************************************");
    int len = strlen(msg.word);
    /*****怎么把解释存储起来？******/
    while (fgets(buf, sizeof(buf), file_fd) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        int ret = strncmp(msg.word, buf, len);
        if (ret == 0 && buf[len] == ' ')
        //利用读到单词得下一个字母横为‘ ’得特性
        {
            char *p = buf + len; //创建一个临时变量p指向单词下一个
            while (*p == ' ')
            {
                p++;
            }
            strcpy(msg.explain, p); //将解析存到单词解释
            strncpy(msg.information, "find\0", 6);
            found = 1; //找到将标志位变为1
            send(fd, &msg, sizeof(msg), 0);
            //将时间和查询得单词记录保存到数据库中
            time_t find_time;
            time(&find_time);
            char l_time[128];
            struct tm *time_fun = localtime(&find_time);
            sprintf(l_time, "%d-%d-%d-%d:%d:%d",
                    time_fun->tm_year + 1900, time_fun->tm_mon + 1,
                    time_fun->tm_mday, time_fun->tm_hour, time_fun->tm_min, time_fun->tm_sec);
            printf("%s\n", l_time);
            char sql[128];
            sprintf(sql, "insert into history values(\"%s\",\"%s\",\"%s\");", msg.name, l_time, msg.word);
            if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
            {
                fprintf(stderr, "sqlite3_exec err:%s", errmsg);
                return -1;
            }

            break;
        }
    }
    //未找到将标志位变为0
    if (found != 1)
    {
        strncpy(msg.information, "not find\0", 10);
        send(fd, &msg, sizeof(msg), 0);
        //将时间和查询得单词记录保存到数据库中
        time_t find_time;
        time(&find_time);
        char l_time[128];
        struct tm *time_fun = localtime(&find_time);
        sprintf(l_time, "%d-%d-%d-%d:%d:%d",
                time_fun->tm_year + 1900, time_fun->tm_mon + 1,
                time_fun->tm_mday, time_fun->tm_hour, time_fun->tm_min, time_fun->tm_sec);
        printf("%s\n", l_time);
        char sql[128];
        sprintf(sql, "insert into history values(\"%s\",\"%s\",\"%s\");", msg.name, l_time, msg.word);
        if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
        {
            fprintf(stderr, "sqlite3_exec err:%s", errmsg);
            return -1;
        }
    }

    fclose(file_fd);
    return 0;
}
//历史记录函数
//需要用到回调函数进行
int server_do_history(int fd, MSG_T msg, sqlite3 *db, char *errmsg)
{
    char sql[128];
    sprintf(sql, "select * from history where name=\"%s\";", msg.name);
    if (sqlite3_exec(db, sql, callback, &fd, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "sqlite3_ exec:%s", errmsg);
        return -1;
    }
    strncpy(msg.information, "end_of\0", 8);
    send(fd, &msg, sizeof(msg), 0);
    return 0;
}

//回调函数
int callback(void *arg, int f_num, char **f_val, char **f_name)
{
    //将传递过来得文件描述符变为原本样子
    int accepfd = *(int *)arg;
    MSG_T back_msg;
    sprintf(back_msg.information, "%s:%s", f_val[1], f_val[2]);
    send(accepfd, &back_msg, sizeof(back_msg), 0);
    return 0;
}