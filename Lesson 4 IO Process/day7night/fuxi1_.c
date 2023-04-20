//使用互斥操作完成同步
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int money = 0;
void *handly(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (money < 100)
        {
            pthread_cond_wait(&cond, &lock);//等待产生条件变量
        }
        money -= 100;
        sleep(1);
        printf("%d \n", money);
        if (money < 100)
        {
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, handly, NULL) != 0)
    {
        perror("tid");
        return -1;
    }

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("lock");
        return -1;
    }

    if (pthread_cond_init(&cond, NULL) != 0)
    {
        perror("cond");
        return -1;
    }

    while (1)
    {
        pthread_mutex_lock(&lock);
        if (money >= 100)
        {
            pthread_cond_wait(&cond, &lock);
        }
        scanf("%d", &money);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock); //上锁问题
    }
    pthread_join(tid, NULL);
    return 0;
}
