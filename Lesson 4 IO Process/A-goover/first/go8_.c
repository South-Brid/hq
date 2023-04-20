//编写程序，使用标准I0,实现往程序里按行书写此时时间
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    time_t newtime;
    struct tm *s;
    char arr[10];
    fp = fopen(argv[1], "a+");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    int i = 1;
    while (fgets(arr, 10, fp) != NULL)
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            i++;
        }
    }
    while (1)
    {
        time(&newtime);
        s = localtime(&newtime);
        fprintf(fp,"%d %d-%d-%d %d-%d-%d\n",i++,s->tm_year+1900,s->tm_mon+1,s->tm_mday\
        ,s->tm_hour,s->tm_min,s->tm_sec);
        sleep(1);
        fflush(fp);
    }
    fclose(fp);
    return 0;
}
