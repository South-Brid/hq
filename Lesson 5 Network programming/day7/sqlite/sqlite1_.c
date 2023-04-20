#include <stdio.h>
#include <sqlite3.h>
int callback(void *arg, int f_num, char **f_val, char **f_name)
{
    // printf("%s", (char *)arg);
    for (int i = 0; i < f_num; i++) //表头名字
    {
        printf("%s ", f_name[i]);
    }
    putchar(10);
    for (int i = 0; i < f_num; i++) //表中元素
    {
        printf("%s ", f_val[i]);
    }
    putchar(10);
    return 0;
}

int main(int argc, char const *argv[])
{
    //1.创建一个数据库 sqlite3_open
    sqlite3 *db = NULL;
    if (sqlite3_open("./stu.db", &db) != SQLITE_OK)
    {
        fprintf(stderr, "sqlite3 open err:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        printf("sqlite 3 ok\n");
    }
    char *errmsg = NULL;
    //2.使用sqlite3_exec创建一个空表 sqlite3_exec
    if (sqlite3_exec(db, 
    "create table stu1(id int,name char,score float);", NULL, NULL, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "create table err:%s\n", errmsg);
        // return -1;
    }
    printf("create ok\n");
    //3.在表中插入数据 sqlite3_exec
    int num;
    int id;
    char name[32];
    float score;
    char sql[128];
    printf("请输入学生人数\n");
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        printf("请输入学号姓名分数\n");
        scanf("%d %s %f", &id, name, &score);
        sprintf(sql, "insert into stu1 values(%d,\"%s\",%f);", id, name, score);
        printf("%s\n", sql);
        /*********************************************************/
        //          sqlite3_exec(1,2,3,4,5)
        //          1为数据库
        //          2为数据库指令，是字符串
        //
        /*********************************************************/
        if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
        {
            fprintf(stderr, "insert err:%s\n", errmsg);
            return -1;
        }
    }
    //4.查看表中数据
    if (sqlite3_exec(db, "select * from stu1;", callback, "hello", &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "insert err:%s\n", errmsg);
        return -1;
    }

    //5.查看表中数据
    char **resultp = NULL;
    int nrow;
    int ncolumn;
    int k = 0;
    if (sqlite3_get_table(db, "select * from stu1;", &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
        fprintf(stderr, "get_table err：%s\n", errmsg);
        return -1;
    }
    for (int i = 0; i < nrow + 1; i++)
    {
        for (int j = 0; j < ncolumn; j++)
        {
            printf(" %s ", resultp[k++]);
        }
        putchar(10);
    }

    sqlite3_close(db);
    return 0;
}
