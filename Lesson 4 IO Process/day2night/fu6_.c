#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    int fp;
    char arr[20]="hello world";
    fp=open("1.txt",O_RDWR|O_CREAT,0666);
    if (fp<0)
    {
        perror("1.txt:");
        return -1;
    }
    write(fp,arr,11);
    close(fp); 
    return 0;
}
