//fputs
#include<stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    fp=fopen("3.txt","w");
    if(fopen == NULL)
    {
        perror("3.txt");
        return -1;
    }
    char arr[32]="ni";
    fputs("hello",fp);
    fputs(arr,fp);
    return 0;
}
