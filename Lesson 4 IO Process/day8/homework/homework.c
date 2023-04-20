#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

struct msg
{
    int flag;
    char buf[32];
};
struct msg p1 = {1, ""};
//创建全局key值
key_t key;

int main(int argc, char const *argv[])
{
    key = ftok("./hello.txt", 'a');
    if (key < 0)
    {
        perror("key");
        return -1;
    }
    //创建父子进程
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
         //创建打开虚拟内存
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
        }

        //映射虚拟内存
        char *p = shmat(shmid, NULL, 0);
        if (p == (char *)-1)
        {

            perror("shmat");
            return -1;
        }

        while (1)
        {
            if (p1.flag == 0)
            {
                printf("%s",p);
            //    fputs(p1.buf,p);
            //     printf("%s", p1.buf);
                p1.flag = 1;
            }
        }
    }
    else //父进程输入
    {
        //创建打开虚拟内存
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
        }

        //映射虚拟内存
        char *p = shmat(shmid, NULL, 0);
        if (p == (char *)-1)
        {

            perror("shmat");
            return -1;
        }


        while (1)
        {
            fgets(p1.buf, 128, stdin);
            if (strcmp(p1.buf, "quite")==0)
            {
                break;
            }
            //将buf内容写到共享内存
            if (p1.flag == 1)
            {
                fputs(p1.buf,p);
                p1.flag = 0;
            }
        }
    }
    return 0;
}
