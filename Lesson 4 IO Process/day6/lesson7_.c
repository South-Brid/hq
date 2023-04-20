#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
char arr[20] = "";
sem_t sem;
void *func(void *arg)
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
    if (pthread_create(&tid, NULL, func, NULL) != 0)
    {
        perror("pthread_create");
        return -1;
    }
    while (1)
    {
        scanf("%s",arr);
        sem_post(&sem);
        if (strcmp("quite", arr) == 0)
        {
            break;
        }
    }
    pthread_join(tid, NULL);
    return 0;
}
