#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fp;
    fp=open("10.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if (fp<0)
    {
        perror("10.txt");
        return -1;
    }
    lseek(fp,10,SEEK_SET);
    write(fp,"a",1);
    off_t x = lseek(fp,0,SEEK_CUR);
    printf("lseek:%ld\n",x);
    return 0;
}
