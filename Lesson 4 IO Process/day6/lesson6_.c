#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

char arr[20] = "";
sem_t sem;

void *hardly(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
        if (strcmp("quite", arr) == 0)
        {
            break;
        }
        puts(arr);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, hardly, NULL) != 0)
    {
        perror("err");
        return -1;
    }

    if (sem_init(&sem, 0, 0) < 0)
    {
        perror("err");
        return -1;
    }

    while (1)
    {
        gets(arr);
        sem_post(&sem);
        if (strcmp("quite", arr) == 0)
        {
            break;
        }
    }
    pthread_join(tid, NULL);
    return 0;
}
