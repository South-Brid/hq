//目录函数实现 ls功能
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    DIR *fp;
    struct dirent *s;
    fp = opendir(".");
    if (fp == NULL)
    {
        perror("error");
        return -1;
    }
    while ((s = readdir(fp)) != NULL)
    {
        if (strcmp(".", s->d_name) != 0 && strcmp("..", s->d_name) != 0)
        {
            printf("%s ", s->d_name);
        }
    }
    closedir(fp);
    return 0;
}
