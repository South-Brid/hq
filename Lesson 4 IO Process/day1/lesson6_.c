/*
fgets函数
fgets(char*a,int size_t,FILE*stream)
功能：读取一串字符

参数：
a:字符数组首地址
size_t:读取得字符个数
stream:文件流

返回值：
成功返回字符串得首地址，失败或者读取完返回NULL


*/
#include <stdio.h>
#include <string.h>
void fg();
int main(int argc, char const *argv[])
{
    fg();
    return 0;
}

void fg()
{
    FILE *fp;
    char arr[100] = {0};
    fp = fopen("text.c", "r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    int num = 0;
    while (fgets(arr,100,fp)!=NULL)
    {
        if (arr[strlen(arr)-1] == '\n')
        {
            num++;
        }
    }
    printf("hang is %d",num);
    fclose(fp);
}