//条件变量实现同步
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int money = 0;
pthread_mutex_t lock;
pthread_cond_t cond; //条件
void *handly(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);

        if (money < 100)
        {
            pthread_cond_wait(&cond, &lock); //等待条件产生
        }
        money -= 100;
        printf("%d\n", money);
        sleep(1);
        if (money < 100)
        {
            pthread_cond_signal(&cond);//产生条件
        }

        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}
int main(int argc, char const *argv[])
{
    pthread_t tip;
    if (pthread_create(&tip, NULL, handly, NULL) != 0)
    {
        perror("err");
        return -1;
    }
    pthread_mutex_init(&lock, NULL);
    if (pthread_cond_init(&cond, NULL) != 0)
    {
        perror("cond_init");
        return -1;
    }
    while (1)
    {
        pthread_mutex_lock(&lock);//上锁
        if (money >= 100)
        {
            pthread_cond_wait(&cond, &lock);//等待条件产生
        }
        scanf("%d", &money);
        pthread_cond_signal(&cond); //产生条件
        pthread_mutex_unlock(&lock);
    }

    pthread_join(tip, NULL);
    return 0;
}
