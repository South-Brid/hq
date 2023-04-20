//函数得同步
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
sem_t sem;
char arr[20] = "";

void *func(void *arg)
{
    while (1)
    {
        sem_wait(&sem);//同步位置很
        if (strcmp(arr, "quite") == 0)
        {
            break;
        }
        printf("%s\n", arr);
    }
    pthread_exit(NULL);
}
int main(int argc, char const *argv[])
{
    pthread_t tip;
    if (0 != pthread_create(&tip, NULL, func, NULL))
    {
        perror("err");
        return -1;
    }
    if (sem_init(&sem, 0, 0) < 0)
    {
        perror("erro");
        return -1;
    }

    while (1)
    {
        scanf("%s", arr);
        sem_post(&sem);
        if (strcmp(arr, "quite") == 0)
        {
            break;
        }
    }
    pthread_join(tip, NULL);
    return 0;
}
