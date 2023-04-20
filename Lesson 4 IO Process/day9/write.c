#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//信号灯共用体
union sem_un {
    int val;
};
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
    //创建共享内存
    int shmid;
    shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid <= 0)
    {
        if (errno == EEXIST)
        {
            shmid = shmget(key, 128, 0666);
        }
        else
        {
            perror("shmget");
            return -1;
        }
    }
    //创建信号灯集合
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
    else //初始化信号灯集
    {
        union sem_un fist;
        //fist.val = 10;
        semctl(semid, 1, SETVAL, fist);
    }
    //映射内存
    char *shm_p = (char *)shmat(shmid, NULL, 0);
    if (shm_p == (char *)-1)
    {
        perror("shmat");
        return -1;
    }

    while (1)
    {
        if (strncmp(shm_p, "quite", 5) == 0)
        {
            break;
        }
        fputs(shm_p, stdout);
        struct sembuf s;
        s.sem_num = 0;
        s.sem_flg = 0;
        s.sem_op = -1; //p操作
        semop(semid, &s, 1);
    }
    shmdt(shm_p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
