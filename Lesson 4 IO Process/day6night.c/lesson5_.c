//互斥锁
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
pthread_mutex_t lock;
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
        sleep(1);
    }
}

void *func2(void *arg)
{
    while (1)
    {
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
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, func1, NULL) != 0)
    {
        perror("err1");
        return -1;
    }
    if (pthread_create(&tid2, NULL, func2, NULL) != 0)
    {
        perror("err2");
        return -1;
    }
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("err3");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
