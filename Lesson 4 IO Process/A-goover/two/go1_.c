//指针流得调用问题
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[10] = "hello";
    char brr[10] = "";
    fp = fopen(argv[1], "a+");
    if (fp == NULL)
    {
        perror("");
        return -1;
    }
    fputs(arr, fp);//将arr内容写到fp
    printf("%ld\n", ftell(fp));//打印此时流指针位置
    rewind(fp); //将流指针定位到文件开头
    printf("%ld\n", ftell(fp));//打印次是流指针得位置
    fgets(brr, 10, fp);//fp文件中得10个元素写到brr中
    printf("%s", brr);//打印brr得内容
    return 0;
}
