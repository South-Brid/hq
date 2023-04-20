#include <stdio.h>
#include <string.h>
#include <unistd.h>
//计算标准输出的缓存区大小
//使用stdout进行计算
void func();
void IntOut();
void func2();
//使用gets
void gets1();
//玩间练习
void night();

int main(int argc, char const *argv[])
{
    night();
    return 0;
}
//玩间练习
void night()
{
    FILE *fp;
    char arr[100];
    fp = fopen("night.txt", "a+");
    if (fp == NULL)
    {
        perror("nighet.txt");
        return;
    }
    int i = 1;
    while (fgets(arr, 100, fp) != NULL)
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            i++;
        }
    }
    while (1)
    {
        fprintf(fp, "%d %s\n", i++, ",hello world");
        fflush(fp);
        sleep(1);
    }
}

//使用gets
void gets1()
{
    FILE *fp;
    char arr[100];
    fp = fopen("text.c", "r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    int i = 0;
    while (fgets(arr, 100, fp) != NULL)
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            i++;
        }
    }
    printf("hang is %d", i);
}

//计算标准输出的缓存区大小
void IntOut()
{
    for (int i = 0; i < 300; i++)
    {
        printf("%4d", i);
    }
    while (1)
        ;
}
//使用stdout进行计算
void func()
{
    printf("hello");
    printf("%d", stdout->_IO_buf_end - stdout->_IO_buf_base);
}
//编程实现计算文件行数功能。要求：fgetc
void func2()
{
    FILE *fp;
    fp = fopen("text.c", "r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            i++;
        }
    }
    printf("hang:%d", i);
}
