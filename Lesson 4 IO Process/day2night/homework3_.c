#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fp;
    fp = open("3.txt", O_RDWR|O_CREAT | O_TRUNC, 0666);
    if (fp < 0)
    {
        perror("3.txt");
        return -1;
    }
    lseek(fp, 9, SEEK_SET);
    write(fp, "a", 1);
    lseek(fp, 19, SEEK_CUR);
    write(fp, "hello", 5);
    off_t x = lseek(fp, 0, SEEK_END);
    printf("file long is %ld", x);
    return 0;
}
