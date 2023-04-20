#include <stdio.h>
#include <string.h>
#include <string.h>
#include <pthread.h>
char arr[20] = "";
sem_t sem;

void *func(void *arg)
{
    while (1)
    {

        if (strcmp(arr, "quite") == 0)
        {
            perror("err");
            return -1;
        }
        printf("%s", arr);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, func, NULL) != 0)
    {
        perror("erro");
        return -1;
    }
    if (sem_init(&sem, NULL) != 0)
    {
        perror("err2");
        return -1;
    }
    while (1)
    {
        scanf("%s", arr);
        if (strcmp(arr, "quite") == 0)
        {
            perror("err");
            return -1;
        }
    }
    return 0;
}
