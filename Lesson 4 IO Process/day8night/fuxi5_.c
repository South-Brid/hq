#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
typedef struct msg
{
    int flag;
    char buf[32];
} msg_t, *msg_p;

int main(int argc, char const *argv[])
{
    key_t key;
    int shmid;
    key = ftok("./fuxi1_.c", 'a');
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
    //创建内存需要使用大小
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

    msg_p p = (msg_p)shmat(shmid, NULL, 0);
    if (p == (msg_p)-1)
    {
        perror("shmat");
        return -1;
    }
    p->flag = 0;
    while (1)
    {

        fgets(p->buf, 32, stdin);
        p->flag = 1;
        if (strncmp(p->buf, "quite",5) == 0)
        {
            break;
        }
    }
    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
