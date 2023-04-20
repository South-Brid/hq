#include<stdio.h>
int main(int argc, char const *argv[])
{
    int date = 0;
    int year,month,day;
    scanf("%d %d %d",&year,&month,&day);
    switch (month)
    {
    case 12:date+=30;
    case 11:date+=31;
    case 10:date+=30;
    case 9:date+=31;
    case 8:date+=31;
    case 7:date+=30;
    case 6:date+=31;
    case 5:date+=30;
    case 4:date+=31;
    case 3:date+=28;
    case 2:date+=31;
    case 1:date+=day;
    default:
    break;
    }
    if ((year % 400 == 0 || (year % 4 == 0 && year %100 !=0)) && month > 2)
    date++;
    printf("%d",date);
    return 0;
}
