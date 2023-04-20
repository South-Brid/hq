//???
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc, char const *argv[])
{
    DIR *fp;
    struct dirent *s;
    fp = opendir("..");
    if (fp == NULL)
    {
        perror("DIR err");
        return -1;
    }
    s = readdir(fp);
    printf("%s ", s->d_name);//每次u读取向后偏移
    s = readdir(fp);
    printf("%s ", s->d_name);
    s = readdir(fp);
    printf("%s ", s->d_name);

    return 0;
}
