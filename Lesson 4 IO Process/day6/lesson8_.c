//互斥锁 成功0 失败-1
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

char arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
pthread_mutex_t lock;
sem_t sem;
void *func1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", arr[i]);
        }
        puts("");
        pthread_mutex_unlock(&lock);
        sleep(1); //必须在sleep前面加锁
    }
}
void *func2(void *arg)
{
    while (1)
    {
        sem_post(&sem);
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 5; i++)
        {
            int x = 0;
            x = arr[i];
            arr[i] = arr[9 - i];
            arr[9 - i] = x;
        }
        pthread_mutex_unlock(&lock);
    }
}
int main(int argc, char const *argv[])
{
    pthread_t tip1, tip2;
    if (pthread_create(&tip1, NULL, func1, NULL) != 0) //这里得函数不能添加括号
    {
        perror("tip1");
        return -1;
    }
    if (pthread_create(&tip2, NULL, func2, NULL) != 0) //这里得函数不能添加括号
    {
        perror("tip2");
        return -1;
    }
    //初始化锁
    if (pthread_mutex_init(&lock, NULL) != 0) //成功返回0,
    {
        perror("lock");
        return -1;
    }

    //同步操作
    if (sem_init(&sem, 0, 0) != 0)
    {
        perror("sem");
        return -1;
    }

    pthread_join(tip1, NULL);
    pthread_join(tip2, NULL);
    return 0;
}
