//fopen函数
#include <stdio.h>

void fopen1();
int main(int argc, char const *argv[])
{
    fopen1();
    return 0;
}
//fopen打开文件函数
void fopen1()
{
    FILE *fp; //文件流指针
    FILE *fc;
    fp = fopen("./text.", "r"); //成功返回FILE* 失败返回NULL，并设置errno
    //第一个参数文件路径，第二个是打开方式
    if (fp == NULL)
    {
        perror("text.c"); //打印错误信息，根据errno得值
        return;
    }
    printf("text.c is ok\n");
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    //判断条件内部赋值,函数得返回值是int型,成功返回对应得ascii数码值，成功返回EOF
    {
        printf("%c", ch);
    }
    /*
    ferror:判断文件出错，出错为真
    feof:判断文件读完，读完为真
     */
    if (ferror(fp))
    {
        puts("error");
    }
    if (feof(fp))
    {
        puts("eof");
    }

    fclose(fp); //关闭文件函数
}