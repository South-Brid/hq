//打印图案
#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i,j,num;
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        for (int j = 0; j<i+1; j++)
        {
            printf("*");
        }
        puts("");
        
    }
    return 0;
}
