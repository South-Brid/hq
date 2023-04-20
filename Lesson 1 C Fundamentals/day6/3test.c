#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i,j;
    for(i=1;i<10;i++)
    {
        for(j=1;j<=i;j++)
        {
            int x = i*j;
            printf("%d*%d=%d ",j,i,x);
        }
        puts("");
    }
    return 0;
}
