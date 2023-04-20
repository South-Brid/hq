#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

struct msg
{
    int flag;
    char buf[32];
};
struct msg p1 = {1, ""};
int main(int argc, char const *argv[])
{

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
            shmid = shmget(key, 128.0666);
        }
        else
        {
            perror("shmget");
            return -1;
        }
    }
    //映射虚拟内存
    char *p = shmat(shmid, NULL, 0);
    if (p == (char *)-1)
    {
        perror("shmat");
        return -1;
    }

    //打开文件
    int pid;
    pid = open(argv[1], O_RDONLY);
    if (pid < 0)
    {
        perror(argv[1]);
        return -1;
    }
    //将文件内容读到虚拟内存
    
    while (p1.buf == 1)
    {
        read(pid, p1.buf, 32);            //将第一个文件内容读到数组
        write(p, p1.buf, sizeof(p1.buf)); //将数组内容放到虚拟内存
        if (read(pid, p1.buf, 32) == 0)
        {
           // p1.buf = 0;
            write(p, p1.flag, 1);
            break;
        }
    }
    return 0;
}
