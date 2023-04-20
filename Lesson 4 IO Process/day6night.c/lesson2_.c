#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int x =0;

void *func(void *arg)
{
    printf("int the func\n");
    printf("func: %d\n",x);
    x++;
}

int main(int argc, char const *argv[])
{
    pthread_t tip;
    if (pthread_create(&tip, NULL, func, NULL) != 0)
    {
        perror("err");
        return -1;
    }


    sleep(1);
    printf("in the main\n");
    printf("main:%d\n",x);
    pthread_join(tip,NULL);
    while(1);
    return 0;
}
