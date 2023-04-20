//求行数得方式
//使用while循环方式
#include <stdio.h>
void fg();
int main(int argc, char const *argv[])
{
    fg();
    return 0;
}
void fg()
{
    FILE *fp;
    char arr[100];
    char *p = NULL;
    fp = fopen("text.c", "r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    int num = 0;
    while ((p = fgets(arr, 100, fp)) != NULL)
    //利用了fgets读到\n后在文件末尾添加\0得特性来计算行数
    {
        while (*p != '\0')
        {
            if (*p == '\n')
            {
                num++;
            }
            p++;
        }
    }
    printf("%d",num);
}