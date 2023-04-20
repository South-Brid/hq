#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
int main(int argc, char const *argv[])
{
    //创建key值
    key_t key = ftok("./hello.txt", 'a');
    if (key < 0)
    {
        perror("key");
        return -1;
    }
    //创建打开共享内存
    int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
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
        printf("%d \n", shmid);
    }
    //映射内存
    char *a = shmat(shmid, NULL, 0);
    if (a == (char *)-1)
    {
        perror("shmat");
        return -1;
    }
    fgets(a,128,stdin);
    printf("fgets:%s\n",a);
    
    return 0;
}
