//向文件中轮换打印时间和行数
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    time_t newtime;
    struct tm * getime;
    char arr[10];
    fp = fopen("fu1.txt", "r+");
    if (fp == NULL)
    {
        perror("fu1.txt");
        return -1;
    }
    int i = 1;
    while (fgets(arr, 10, fp) != NULL)//fgets函数得加强
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            i++;
        }
    }
    while (1)
    {
        time(&newtime);
        getime =localtime(&newtime);
        fprintf(fp,"%d %d-%d-%d %d-%d-%d \n",i++,getime->tm_year+1900,\
        getime->tm_mon+1,getime->tm_mday,getime->tm_hour,getime->tm_min\
        ,getime->tm_sec);
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
    return 0;
}
