
//sem函数，同步
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char arr[20] = "";
sem_t sem;

void *handly(void *arg)
{
    while (1)
    {
        sem_wait(&sem);//p操作，申请资源-
        if (strcmp(arr, "quite") == 0)
        {
            break;
        }
        printf("%s\n", arr);
    }
    pthread_exit(NULL); //结束子线程
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, handly, NULL) != 0) //创建线程
    {
        puts("err");
        return -1;
    }

    if (sem_init(&sem, 0, 0) < 0)//成功返回0,失败返回-1
    {
        perror("sem");
        return -1;
    }
    while (strcmp(arr, "quite") != 0)
    {
    
        gets(arr);
        sem_post(&sem);//v操作 释放资源，+
    }
    pthread_join(tid, NULL); //记得回收线程
    return 0;
}
