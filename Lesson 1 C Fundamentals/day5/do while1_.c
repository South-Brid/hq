#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i=1;
    int sum =0;
    do
    {
        sum+=i;
        i++;
    }while(i<=10);//一定要加;
    printf("%d \n",sum);
    return 0;
}
