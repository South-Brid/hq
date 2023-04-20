//此时程序还没引入锁得概念
//只能用全局变量进行操作
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
char arr[20] = "";
int n = 0;

void *handly(void *tid)
{
    while (strcmp(arr, "quite") != 0)
    {
        if (n)
        {
            printf("%s\n", arr);
            n = 0;
        }
    }
}
int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, handly, &tid) != 0)
    {
        perror("cteate err");
        return -1;
    }

    while (strcmp(arr, "quite") != 0)
    {
        gets(arr);
        n = 1;
    }
    pthread_join(tid,NULL);//补充
    return 0;
}
