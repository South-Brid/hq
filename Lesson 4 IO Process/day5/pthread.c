//查看进程的命令 ps -eLf|grep a.out

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//定义线程的函数
//在编译线程函数的时候需要加上-lpthread
void *fun(void *arg)
{
    printf("THIS IS THREAD FUNCTION \n");
    //d exit(0);
}
void *fun2(void *arg)
{
    printf("THIS IS THREAD FUNCTION2 \n");
}

int main()
{
    //线程1创建
    pthread_t tid; //定义id结构体用来使用
    int err;
    err = pthread_create(&tid, NULL, fun, NULL);
    if (err != 0)
    {
        printf("create thread :%s\n", strerror(err));
        return -1;
    }
    sleep(1);
    //线程的回收
    err = pthread_join(tid, NULL);

    //线程2创建
    int str;
    str = pthread_create(&tid, NULL, fun2, NULL);
    if (str != 0)
    {
        printf("create thread :%s\n", strerror(str));
        return -1;
    }
    //线程的回收
    str = pthread_join(tid, NULL);
    sleep(1);
}
//父线程退出，子线程也跟着退出
//在线程中，一个线程函数执行退出程序，整个线程都会结束
