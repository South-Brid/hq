//分析下面代码
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#define _LOCK_ 	//没有定义_locK
unsigned int value1, value2, count;
pthread_mutex_t mutex;
void *function(void *arg);
int main(int argc, char *argv[])
{
    pthread_t a_thread;
    if (pthread_mutex_init(&mutex, NULL) < 0) //初始化锁
    {
        perror("fail to mutex_init");
        exit(-1);
    }
    if (pthread_create(&a_thread, NULL, function, NULL) < 0) //创建一个子流程
    {
        perror("fail to pthread_create");
        exit(-1);
    }
    //父流程当中
    while (1)
    {
        count++; //循环让count+1
#ifdef _LOCK_
        pthread_mutex_lock(&mutex); //加锁  	//如果定义了lock就加锁
#endif
        value1 = count; //让value1和value2等于count
        value2 = count; //操作临界资源
#ifdef _LOCK_
        pthread_mutex_unlock(&mutex); //解锁	//如果定义了lock就解锁
#endif
    }
    return 0;
}

//子流程当中
void *function(void *arg)
{
    while (1)
    {
#ifdef _LOCK_
        pthread_mutex_lock(&mutex); //加锁			//如果定义了lock就加锁
#endif
        if (value1 != value2) //当两者不相等时
        {
            printf("count=%d , value1=%d, value2=%d\n", count, value1, value2);
            usleep(100000); //打印value1和value2和count的值
        }
#ifdef _LOCK_                         //如果定义了lock就解锁
        pthread_mutex_unlock(&mutex); //解锁
#endif
    }
    return NULL;
}
/*
上述程序在未添加互斥锁得情况下，父流程得中在死循环得作用下value1和value2和count值会快速得持续增加，子流程
在判断中value1和value2在
*/