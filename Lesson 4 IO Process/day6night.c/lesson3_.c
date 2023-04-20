//全局变量法
#include <stdio.h>
#include <pthread.h>
#include <string.h>
int i = 0;
char arr[20] = "";
void *func(void *arg)
{
    while (strcmp("quite", arr) != 0)
    {
        if (i)
        {
            printf("%s\n", arr);
            i = 0;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t tip;
    if (pthread_create(&tip, NULL, func, NULL) != 0)
    {
        perror("err");
        return -1;
    }

    while (strcmp("quite", arr) != 0)
    {
        scanf("%s", arr);
        i = 1;
    }
    pthread_join(tip, NULL);
    return 0;
}
