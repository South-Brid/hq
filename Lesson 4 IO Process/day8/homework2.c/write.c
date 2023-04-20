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

    key = ftok("./hello", 'a');                                    //创建key值
    int shmid = shmget(key, sizeof(struct msg), IPC_CREAT | 0666); //创建内存
    if (shmid < 0)
    {
        perror("shmget");
        return -1;
    }

    struct msg *pmsg = (struct msg *)shmat(shmid, NULL, 0); //映射内存
    if (pmsg == (void *)-1)
    {
        perror("shmat");
        return -1;
    }

    pmsg->flag = 0; //赋值为0

    while (1)
    {
        char buf[32] = {0};
        printf("请输入: ");
        fgets(buf, sizeof(buf), stdin);             //从端口获取输入
        strncpy(pmsg->buf, buf, sizeof(pmsg->buf)); //将buf覆盖到内存中得pmsg->buf
        pmsg->flag = 1;                             //将共享内存中得buf置为1
        if (strncmp(buf, "quit", 4) == 0)
            break;
    }

    shmdt(pmsg);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
