#include<stdio.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    char arr[10]="helloworld";
    char brr[10]="";
    fp=fopen("fu1.txt","w+");
    if (fp == NULL)
    {
        perror("fu1.txt");
        return -1;
    }
    fwrite(arr,sizeof(char),10,fp);
    rewind(fp);
    fread(brr,sizeof(char),10,fp);
    //参数规律 数组在前，文件流在后
    printf("%s",brr);
    fclose(fp);
    return 0;
}
