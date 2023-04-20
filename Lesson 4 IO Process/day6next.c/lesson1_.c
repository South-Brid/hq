#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *func(void *arg)
{
    printf("in the func\n");
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, func, NULL) != 0)
    {
        perror("err1");
        return -1;
    }
    sleep(1);
    printf("in the main\n");
    pthread_join(tid,NULL);
    return 0;
}