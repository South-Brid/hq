#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define max 5
void babu();
void chose();
void china();
int num_zhi();
char *arr_num(char arr[]);
void exchange(int *a, int *b);
void malloc_free();

int main(int argc, char const *argv[])
{
#if 0
    chose();
    china();
    int a=5;
    int b=6;
    printf("%d %d %d\n",a,b,num_zhi(&a,&b));
    char *p =arr_num("123");
    printf("%s\n",p);
    int a = 5;
    int b = 6;
    printf("a=%d b=%d\n", a, b);
    exchange(&a, &b);
    printf("a=%d b=%d\n", a, b);
#endif
    malloc_free();
    return 0;
}
//?????
void malloc_free()
{
    int *p = (int *)malloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++)
    {
        (*p) += 1;
        printf("%d", *p);
    }
    free(p);
    p = NULL;
}

//exchange
void exchange(int *pa, int *pb)
{
    int x = 0;
    x = *pa;
    *pa = *pb;
    *pb = x;
}

//arr_zhizhen
char *arr_num(char arr[])
{
    arr = "string";
    return arr;
}

//num_zhi
int num_zhi(int *a, int *b)
{
    (*a)++;
    //???????????????????
    (*b)++; //????????
    return *a + *b;
}
//china
void china()
{
    char ch[32] = "i love china";
    char *pa = ch;
    char *pb = ch + strlen(ch) - 1;
    char *pc = NULL;
    char x;
    while (pa < pb)
    {
        x = *pa;
        *pa = *pb;
        *pb = x;
        pa++;
        pb--;
    }
    pa = pb = ch; //
    while (*pb)
    {
        while (*pb == ' ')
        {
            pb++;
        }
        pa = pb;
        while (*pb != '\0' && *pb != ' ')
        {
            pb++;
        }
        pc = pb;
        pb--;
        while (pa < pb)
        {
            x = *pa;
            *pa = *pb;
            *pb = x;
            pa++;
            pb--;
        }
        pb = pc;
    }
    int i;
    printf("%s", ch);
}

//chose
void chose()
{
    int arr[max] = {5, 4, 3, 2, 1};
    int i, j, k, l;
    for (i = 0; i < max - 1; i++)
    {
        k = i;
        for (j = i + 1; j < max; j++)
        {
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }
        if (arr[k] != arr[i])
        {
            l = arr[k];
            arr[k] = arr[i];
            arr[i] = l;
        }
    }
    for (i = 0; i < max; i++)
    {
        printf("%d ", arr[i]);
    }
}

//babu
void babu()
{
    int arr[max] = {5, 7, 9, 6, 2};
    int i, j, k;
    for (i = 0; i < max - 1; i++)
    {
        for (j = 0; j < max - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
        }
    }
    for (i = 0; i < max; i++)
    {
        printf("%d ", arr[i]);
    }
}