//信号灯集函数
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union sem_un {
    int val;
};

//初始化封装函数
union sem_un Clear(int num,int val_num,int sem_post)
{

    static union sem_un sem;
    sem.val = val_num;
    semctl(num,sem_post, SETVAL, sem);
    return sem;
}

//pv操作函数
void PVfunc(struct sembuf *s, int semid, int num1, int num2)
{
    s->sem_num = num1;
    s->sem_op = +1;
    s->sem_flg = 0;
    semop(semid, s, 1); //最后一个是调用得灯得个数

    s->sem_num = num2;
    s->sem_op = -1;
    s->sem_flg = 0;
    semop(semid, s, 1); //最后一个是调用得灯得个数
}

int main(int argc, char const *argv[])
{
    //创建key值
    key_t key;
    key = ftok("./", 'x');
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
    //创建打开信号灯集
    //每次都需要ipcs -s查看信号灯集状态
    //然后使用ipcrm -s semid 删除信号灯
    int semid;
    semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);
    if (semid <= 0)
    {
        if (errno == EEXIST)
        {
            semid = semget(key, 2, 0666);
        }
        else
        {
            perror("semget");
            return -1;
        }
    }
    else
    {
        //初始化信号灯集合
        union sem_un sem = Clear(semid);
        // sem.val = 0;
        // semctl(semid, 0, SETVAL, sem);
        // sem.val = 10;
        // semctl(semid, 1, SETVAL, sem);
    }
    // int x = semctl(semid, 0, GETVAL);
    // int y = semctl(semid, 1, GETVAL);
    // printf("初始信号灯0：%d\n", x);
    // printf("初始信号灯1：%d\n", y);
    // printf("key:%#x\n",key);
    // printf("semid:%d\n",semid);
    //对信号灯集进行p和v操作
    struct sembuf s;
    // s.sem_num = 0;       //信号灯号
    // s.sem_op = +1;       //v操作
    // s.sem_flg = 0;       //参数，0代表阻塞
    // semop(semid, &s, 1); //最后一个是调用得灯得个数

    // s.sem_num = 1;
    // s.sem_op = -1;
    // s.sem_flg = 1;
    // semop(semid, &s, 1); //最后一个是调用得灯得个数
     PVfunc(&s,semid,0, 10);

    printf("信号灯0号：%d\n", semctl(semid, 0, GETVAL));
    printf("信号灯1号：%d\n", semctl(semid, 1, GETVAL));

    // semctl(semid, 0, IPC_RMID);
    return 0;
}
