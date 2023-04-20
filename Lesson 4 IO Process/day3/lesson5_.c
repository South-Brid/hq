#include <stdio.h>
#define N 5
typedef struct book
{
    int book_num;
    char book_name[20];
    float book_money;
} book_t, *book_p;

void myfunc(book_t *p, float num);

int main(int argc, char const *argv[])
{
    book_t arr[N] = {{1, "halibote", 158.3}, {2, "wudidaliwang", 198.8}, {3, "nishuosha", 178}};
    myfunc(arr, 100);
    return 0;
}

void myfunc(book_t *p, float num)
{
    for (int i = 0; i < N; i++)
    {
        if (p[i].book_money > num)
        {
            printf("%d %s %.2f \n", p[i].book_num, p[i].book_name, p[i].book_money);
        }
    }
}
