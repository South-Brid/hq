#include <stdio.h>
#define max 5
typedef struct book
{
    int book_number;
    char book_name[30];
    float book_money;
} bo;
int big_money(bo *pa, int x);
int main(int argc, char const *argv[])
{
    struct book list[max];
    int x_money = 0;
    puts("请输入价格");
    scanf("%d", &x_money);
    big_money(list, x_money);
    return 0;
}

int big_money(bo *pa, int x_num)
{
    puts("请输入想要存得书本数量");
    int x;
    int i;
    scanf("%d", &x);
    for (i = 0; i < x; i++)
    {
        puts("请依次输入书的书号，姓名，价格");
        scanf("%d %s %f", &pa[i].book_number, pa[i].book_name, &pa[i].book_money);
        //p[i]是元素，p+i是地址，遗忘了这点
    }

    for (i = 0; i < x; i++)
    {
        if (x_num < pa[i].book_money)
        {
            printf("书号：%d 书名：%s 书价：%.2f\n",
                   pa[i].book_number,
                   pa[i].book_name,
                   pa[i].book_money);
            return 1;
        }
    }
    puts("没有比价格高的书");
    return -1;
}
