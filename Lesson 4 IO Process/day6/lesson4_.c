#include <pthread.h>
#include <stdio.h>
#include <string.h>

char arr[20] = "";
int x = 0;//标志位
void *handly(void *arg)
{
    while (strcmp(arr, "quite") != 0)
    {
        if (x)
        {
            printf("%s\n", arr);
            x = 0;
        }
    }
    pthread_exit(NULL);//结束子线程
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, handly, NULL) != 0)//创建线程
    {
        puts("err");
        return -1;
    }
    while (strcmp(arr, "quite") != 0)
    {
        gets(arr);
        x = 1;
    }
    pthread_join(tid, NULL);//记得回收线程
    return 0;
}
