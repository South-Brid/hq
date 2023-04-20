#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

key_t key;

struct msg
{
    int flag;
    char buf[32];
};

int main(void)
{
    key = ftok("./hello", 'a');
    int shmid = shmget(key, sizeof(struct msg), IPC_CREAT | 0666);
    if (shmid < -1)
    {
        perror("shmget");
        return -1;
    }

    struct msg *pmsg = (struct msg *)shmat(shmid, NULL, 0); //神来之笔
    if (pmsg == (void *)-1)
    {
        perror("shmat");
        return -1;
    }

    while (1)
    {
        if (pmsg->flag) //0不执行1执行
        {
            printf("结果: %s", pmsg->buf);
            pmsg->flag = 0;
            if (strncmp(pmsg->buf, "quit", 4) == 0)
                break;
        }
        sleep(1);
    }
    shmdt(pmsg);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
