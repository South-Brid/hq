#include<stdio.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    int arr[]={100,200,300};
    int brr[3]={0};
    fp=fopen("read.txt","w+");
    if (fp == NULL)
    {
        perror("read.txt");
        return -1;
    }
    fwrite(arr,sizeof(int),3,fp);
    //功能：将数据写入fp文件流当中
    //参数：arr：写入得内容地址
    //      sizeof(int):写入内容一个所占得字节大小
    //      3：写入得内容个数
    //      fp：被写入得文件流
    rewind(fp);
    //功能：将指针流定位到开头
    //参数：文件流
    fread(brr,sizeof(int),3,fp);
    //功能将文件中得内容读取到制定位置
    //参数：brr接收从文件读取得数据
    //sizeof(int):文件中读取得一个数据所占得字节
    //3:读取得数据个数
    //fp：被读取得文件
    for (int i = 0; i < 3; i++)
    {
        printf("%d ",brr[i]);
    }
    fclose(fp);
    return 0;
}
