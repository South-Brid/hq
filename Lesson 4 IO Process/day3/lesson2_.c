//目录函数
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    DIR *fp;
    struct dirent *dr;
    fp = opendir("..");
    if (fp == NULL)
    {
        perror("opendir");
        return -1;
    }
    // while ((dr = readdir(fp)) != NULL)
    // {
    //     if (dr->d_name[0] != '.')
    //     {
    //         printf("%s ", dr->d_name);
    //     }
    // }
    while ((dr = readdir(fp)) != NULL)
    {
        if (strcmp(dr->d_name, ".") != 0 && strcmp(dr->d_name, "..") != 0)
        //此处得用&&，还有字符串之间进行比较使用strcmp
        {
            printf("%s ", dr->d_name);
        }
    }
    return 0;
}
