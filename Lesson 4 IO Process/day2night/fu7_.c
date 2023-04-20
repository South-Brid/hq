#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fp;
    int fw;
    char arr[10];
    fp = open("1.txt", O_RDONLY);
    if (fp < 0)
    {
        perror("1.txt");
        return -1;
    }
    fw = open("2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fw < 0)
    {
        perror("2.txt");
        return -1;
    }
    ssize_t x ;
    while ((x = read(fp, arr, 10)) != 0)
    {
        write(fw, arr, x);
    }
    close(fp);
    close(fw);
    return 0;
}
