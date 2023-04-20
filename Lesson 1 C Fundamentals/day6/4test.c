#include <stdio.h>
int main(int argc, char const *argv[])
{
    int year, month, day;
    int x = 0;
    scanf("%d %d %d", &year, &month, &day);
    switch (month)
    {
    case 12:
        x += 30;
    case 11:
        x += 31;
    case 10:
        x += 30;
    case 9:
        x += 31;
    case 8:
        x += 31;
    case 7:
        x += 30;
    case 6:
        x += 31;
    case 5:
        x += 30;
    case 4:
        x += 31;
    case 3:
        x += 28;
    case 2:
        x += 31;
    case 1:
        x += day;
    }
if ((year % 4 == 0 && year % 100 != 0 || year % 400 == 0) && month > 2)
{
    x++;
}
printf("%d",x);
return 0;
}