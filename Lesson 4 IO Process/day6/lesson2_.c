//pthread_create创建子线程函数
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
int x = 66; //定义全局变量

void *handler(void *arg) //子线程
{
    printf("in thread\n");
    x = x + 100;
    printf("注意强转问题：%d\n", *(int *)arg); //这里这里进行强转
}
int main(int argc, char const *argv[])
{
    pthread_t tid;
    int n = 100;

    if (pthread_create(&tid, NULL, handler, &n) != 0) //第一个参数得取地址
    //pthread_create(&tid, NULL,handler,&n),成功返回0
    {
        perror("create err");
        return -1;
    }

    //主线程--从这往后
    pthread_join(tid,NULL);//回收线程得资源，此时是阻塞函数
    sleep(1);
    printf("int main\n");
    printf("全局变量：%d\n", x);
   // pthread_exit(NULL);//结束线程
    while (1)
        ;
    return 0;
}
