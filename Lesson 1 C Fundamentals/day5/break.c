#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i;
    for(i=1;i<10;i++)
    {
        if(i == 4)
            //break;
            continue;
        printf("%d ",i);
    }
    return 0;
}