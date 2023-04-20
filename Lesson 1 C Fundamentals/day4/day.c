#include<stdio.h>
int main()
{
    int x=0;
    int year,mon,day;
    scanf("%d %d %d",&year,&mon,&day);
    switch (mon)
    {
        case 12:x+=30;
        case 11:x+=31;
        case 10:x+=30;
        case 9:x+=31;
        case 8:x+=31;
        case 7:x+=30;
        case 6:x+=31;
        case 5:x+=30;
        case 4:x+=31;
        case 3:x+=28;
        case 2:x+=31;
        case 1:x+=day;
        default:
            break;
    }
    if(year%100==0 || (year % 4 == 0 && year % 100 !=0) && mon>2 )
    x++;
    printf("%d",x);
    return 0;
}