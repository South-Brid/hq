#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

struct msgbuf
{
    long type;
    char name[32];
    int age;
};

int main(int argc, char const *argv[])
{
    key_t key;
    key = ftok("./", 'x');
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
    int msgid;
    msgid = msgget(key, IPC_CREAT|IPC_EXCL | 0666);
    if (msgid <= 0)
    {
        if (errno == EEXIST)
        {
            msgid = msgget(key, 0666);
        }
        else
        {
            perror("msgget");
            return -1;
        }
    }
    struct msgbuf msg;
    msg.type = 1; //不能为0
    strcpy(msg.name, "hqyj");
    msg.age = 24;
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 1);

    msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0);

    printf("msg name:%s\n", msg.name);
    printf("msg age:%d\n", msg.age);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
