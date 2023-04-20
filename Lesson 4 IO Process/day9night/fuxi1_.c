//信号灯集API函数得调用
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
typedef union {
    int val;
} sem_t, *sem_p;

int main(int argc, char const *argv[])
{
    key_t key;
    key = ftok("./", 'x');
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
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
        sem_t s;
        s.val = 0;
        semctl(semid, 0, SETVAL, s); //不需要传递地址
        s.val = 10;
        semctl(semid, 1, SETVAL, s);
    }
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_flg = 0;
    buf.sem_op = 1;
    semop(semid, &buf, 1);

    buf.sem_num = 1;
    buf.sem_flg = 0;
    buf.sem_op = -1;
    semop(semid, &buf, 1);

    printf("0deng:%d\n",semctl(semid,0,GETVAL));
    printf("0deng:%d\n",semctl(semid,1,GETVAL));

    semctl(semid,0,IPC_RMID);

    return 0;
}
