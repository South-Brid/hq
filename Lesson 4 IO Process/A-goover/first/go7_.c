//使用标准io实现向文件隔一秒书写内容得功能
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[20];
    fp = fopen(argv[1], "a+");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    int i = 1;
    while (fgets(arr, 20, fp) != NULL)
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            i++;
        }
    }
    while (1)
    {
        fprintf(fp, "%d %s \n", i++, "welcome new world");
        //面向文件，\n无法刷新，得使用fflush进行强制刷新
        fflush(fp);
        sleep(1);

    }
    return 0;
}
