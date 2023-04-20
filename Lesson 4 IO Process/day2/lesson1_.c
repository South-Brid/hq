#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

    time_t nowtime;  //定义time_t类型得变量
    struct tm *info; //定义tm结构体（我也不知道tm是啥），创建对象info

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
        time(&nowtime); //将time_t类型变量传到time函数，此时参数也能拿到
        info = localtime(&nowtime);
        fprintf(fp, "%d %s\n", i++, asctime(info));
        fflush(fp);
        sleep(1);
    }
}