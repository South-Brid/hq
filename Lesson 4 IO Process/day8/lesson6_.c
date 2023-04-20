//创建key值用来标识共享内存
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    key_t key = ftok(argv[1], 'a');
    printf("%#x", key);
    return 0;
}
