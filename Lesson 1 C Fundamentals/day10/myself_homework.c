#include <stdio.h>
#include <string.h>
void myself_cpy(char *pa, char *pb);
void myself_cat(char *pc, char *pd);
int myself_cmp(char *a, char *b);

int main(int argc, char const *argv[])
{
    char arr[10] = "aello";
    char brr[10] = "bello";
    //myself_cpy(arr, brr);
    //myself_cat(arr, brr);
    printf("%d",myself_cmp(arr, brr));
    //puts(arr);
    return 0;
}
//实现strcmp函数
int myself_cmp(char *a, char *b)
{
    int i, j;
    int x = strlen(a) > strlen(b) ? strlen(a) : strlen(b);
    for (i = 0; i < x; i++)
    {
        if (a[i] != b[i])
        {
            return a[i] - b[i];
        }
    }
    return 0;
}
//实现strcat函数
void myself_cat(char *pc, char *pd)
{
    while (*pc)
    {
        pc++;
    }
    while (*pd)
    {
        *pc = *pd;
        pc++;
        pd++;
    }
    *pc = *pd;
}

//实现strcpy函数
void myself_cpy(char *pa, char *pb)
{
    while (*pb)
    {
        *pa = *pb;
        pb++;
        pa++;
    }
    *pa = *pb; //注意此处
}