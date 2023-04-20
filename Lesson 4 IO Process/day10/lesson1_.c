#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

struct msgbuf
{
    long type;
    char arr[32];
    int age;
};

int main(int argc, char const *argv[])
{
    key_t key;
    key = ftok("./", 'x'); //密码使用文件路径和字符创建
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
    int msgid;
    msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666); //从创建消息队列
    if (msgid <= 0)
    {
        if (errno == EEXIST)
        {
            msgid = msgget(key, 0666);
        }
        else
        {
            perror("megget");
            return -1;
        }
    }
    struct msgbuf msg = {3, "test1", 38};
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 3);
    //参数：msgid 结构体地址 除了第一个long以外得所有类型 发送得信号标识
    //  msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 0, 0);


    msg.type = 2;
    strcpy(msg.arr, "test2");
    msg.age = 80;

    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 2);
    msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 2, 0);
    //参数：msgid 结构体地址 除了第一个long以外得所有类型 发送得信号标识 0代表阻塞

    msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 0, 0);
    printf("msg name:%s\n", msg.arr);
    printf("msg age:%d\n", msg.age);

    //printf("%d\n",msgid);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
