//实现时间得计算
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    time_t nowtime;
    struct tm *htime;
    char arr[100];
    fp = fopen("time.txt", "a+");
    if (fp == NULL)
    {
        perror("time.txt");
        return -1;
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
        time(&nowtime);              //通过参数就能计算出时间
        htime = localtime(&nowtime); //转换格式
        fprintf(fp, "%d,%d-%d-%d %d-%d-%d\n", i++, htime->tm_year + 1900, htime->tm_mon + 1,
                htime->tm_mday, htime->tm_hour, htime->tm_min, htime->tm_sec);
        fflush(fp);
        sleep(1);
    }

    return 0;
}
