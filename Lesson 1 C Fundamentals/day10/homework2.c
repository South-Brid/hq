#include <stdio.h>
typedef struct student
{
    int num;
    char name[100];
    int garde;
} STU;

int main(int argc, char const *argv[])
{
    STU arr[3];
    int i;
    for (i = 0; i < 3; i++)
        scanf("%d %s %d", &arr[i].num, arr[i].name, &arr[i].garde);
    for (i = 0; i < 3; i++)
        if (arr[i].garde < 60)
            printf("%s同学不及格", arr[i].name);
    return 0;
}
