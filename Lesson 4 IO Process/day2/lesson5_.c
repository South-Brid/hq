#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    fp = fopen("5.txt", "w+");
    if (fp == NULL)
    {
        perror("5.txt");
        return -1;
    }
    fseek(fp, 10, SEEK_SET);//10
    /*
    功能：偏移流指针得位置
    参数：
    1.要偏移得文件流
    2.偏移得个数
    3.偏移开始得位置
    关于偏移得开始位置得相关参数
    SEEK_SET    头部
    SEEK_CUR    当前位置
    SEEK_END    结束位置
     */
    fputc('a', fp);//11
    fseek(fp, 10, SEEK_CUR);//21
    fputs("12345", fp);//26
    long l = ftell(fp);
    printf("长度：%ld", l);

    return 0;
}
