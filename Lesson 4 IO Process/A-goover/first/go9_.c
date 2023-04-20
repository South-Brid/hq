//fread和fwrite使用方法
//注意，这是二进制得读写
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    int arr[5]={10,20,30,40,50};
    int brr[5]={};
    fp = fopen(argv[1], "w+");
    if (fp == NULL)
    {
        perror("err");
        return -1;
    }
    fwrite(arr,sizeof(int),5,fp);
    rewind(fp);
    fread(brr,sizeof(int),5,fp);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ",brr[i]);
    }
    return 0;
}
