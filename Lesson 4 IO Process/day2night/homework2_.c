//使用标准io实现cp
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    FILE*fw;
    fp=fopen(argv[1],"r");
    if (fp == NULL)
    {
        perror("fist:");
        return -1;
    }
    fw=fopen(argv[2],"w");
    if (fw == NULL)
    {
        perror("next:");
        return -1;
    }
    if (argc != 3)
    {
        printf("please use :%s \
        <oldfilename> <newfilename>",argv[0]);
        return-1;
    }
    char ch[10];
    while (fgets(ch,10,fp) != NULL)
    {
        fputs(ch,fw);
    }
    fclose(fp);
    fclose(fw);
    return 0;
}
