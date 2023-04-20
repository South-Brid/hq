#include<stdio.h>
int main(int argc, char const *argv[])
{
    FILE*fp;
    fp=fopen("1.txt","a");
    freopen("./2.txt","r+",fp);
    return 0;
}
