//fputs的用法
#include<stdio.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    fp=fopen("fu1.txt","w");
    if (fp == NULL)
    {
        perror("fu1.txt");
        return -1;
    }
    fputs("hello",fp);
    fclose(fp);
    return 0;
}
