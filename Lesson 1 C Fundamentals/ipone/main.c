//还得是指针
#include <stdio.h>
#include <string.h>
#define MAX 1000
//宏定义
//结构体
typedef struct Students
{
    char name[50];
    int age;
    int sex;
    char address[50];
} STU;

typedef struct lessnumber
{
    int number;
    STU list[MAX]; //结构体数组
} LES;
//函数声明
void pr_chose();
int chose_num();
void addperson(LES *new);
void findtest(LES *find_num);
int find_person(LES *fi_pe, char *pa);
void delete_person(LES *de_pr);
int find_4(LES *find_person_4);
int xiugai(LES *xiu_person_5);
void clean_test(LES *clean);

int main(int argc, char const *argv[])
{
    int x;
    LES list_num;
    pr_chose(); //打印界面
    while (1)
    {
        x = chose_num();
        switch (x)
        {
        case 1:
            addperson(&list_num);
            pr_chose();
            continue;
        case 2:
            findtest(&list_num);
            pr_chose();
            continue;
        case 3:
            delete_person(&list_num);
            pr_chose();
            continue;
        case 4:
            find_4(&list_num);
            pr_chose();
            continue;
        case 5:
            xiugai(&list_num);
            continue;
        case 6:
            clean_test(&list_num);
            continue;
        case 7:
            break;
        default:
            continue;
        }
        break;
    }
    return 0;
}
//函数定义
//清空通讯录
void clean_test(LES *clean)
{
    int num = 0;
    puts("你确定要清空通讯录吗？");
    puts("1.确定");
    scanf("%d",&num);
    if (num == 1)
    {
        clean->number = 0;
    }
    
}
//修改信息函数
int xiugai(LES *xiu_person_5)
{
    char xiugai_5_name[100];
    puts("请输入想要修改的成员姓名");
    scanf(" %[^\n]", xiugai_5_name);
    int i;
    for (i = 0; i <= xiu_person_5->number; i++)
    {
        if (strcmp(xiu_person_5->list[i].name, xiugai_5_name) == 0)
        {
            puts("请填写您的个人信息:");
            puts("姓名：");
            scanf(" %[^\n]", xiu_person_5->list[i].name);
            while (1)
            {
                puts("年龄：");
                scanf(" %d", &xiu_person_5->list[i].age);
                if (xiu_person_5->list[i].age > 0 && xiu_person_5->list[i].age < 150)
                {
                    break;
                }
                puts("你是真的牛皮");
            }
            while (1)
            {
                puts("性别:1男2女");
                scanf(" %d", &xiu_person_5->list[i].sex);
                if (xiu_person_5->list[i].sex == 1 || xiu_person_5->list[i].sex == 2)
                {
                    break;
                }
                puts("你选择了奇怪的性别，请重新输入");
            }

            puts("地址：");
            scanf(" %[^\n]", xiu_person_5->list[i].address);
            puts("修改成功");
            return 1;
        }
    }
    puts("为找到人员");
    return -1;
}

//查找人员函数
int find_4(LES *find_person_4)
{
    char find_4_name[100];
    puts("请输入想要查找的成员姓名");
    scanf(" %[^\n]", find_4_name);
    int i;
    for (i = 0; i <= find_person_4->number; i++)
    {
        if (strcmp(find_person_4->list[i].name, find_4_name) == 0)
        {
            puts("找到了，您要查找的人信息如下");
            printf("%s  ", find_person_4->list[i].name); //这里存疑
            printf("%d  ", find_person_4->list[i].age);
            find_person_4->list[i].sex == 1 ? printf("男  ") : printf("女  ");
            printf("%s  \n", find_person_4->list[i].address);
            return 1;
        }
    }
    puts("没有找到");
    return -1;
}

//删除人员
void delete_person(LES *de_pr)
{
    puts("请输入要删除人员的姓名");
    static char name[50] = {};
    //存疑
    scanf(" %[^\n]", name);
    int x = find_person(de_pr, name);
    if (x == -1)
    {
        puts("查无此人");
    }
    else
    {
        for (int i = x; i < de_pr->number; i++) //删除函数的核心代码
        //x接受的是通讯录数组的下标
        {
            de_pr->list[i] = de_pr->list[i + 1];
            //让高一位数组的通讯录的下标覆盖要删除的通讯录的下标
        }
        de_pr->number--;
        puts("删除成功");
    }
}

//查找人员函数
//通过数值来执行选择思想
int find_person(LES *fi_pe, char *pa)
{
    int i;
    for (i = 0; i < fi_pe->number; i++)
    {
        if (strcmp(fi_pe->list[i].name, pa) == 0)
            //记住函数strcmp
            return i;
    }
    return -1;
}

//显示人员
void findtest(LES *find_num)
{
    if (find_num->number == 0)
    {
        puts("内部为空");
    }
    else
    {
        int i;
        for (i = 0; i < find_num->number; i++)
        {
            printf("%s  ", find_num->list[i].name); //这里存疑
            printf("%d  ", find_num->list[i].age);
            find_num->list[i].sex == 1 ? printf("男  ") : printf("女  ");
            printf("%s  \n", find_num->list[i].address);
        }
    }
}

//增加人员函数
void addperson(LES *new)
{
    puts("请填写您的个人信息:");
    puts("姓名：");
    scanf(" %[^\n]", new->list[new->number].name);
    while (1)
    {
        puts("年龄：");
        scanf(" %d", &new->list[new->number].age);
        if (new->list[new->number].age > 0 && new->list[new->number].age < 150)
        {
            break;
        }
        puts("你是真的牛皮");
    }
    while (1)
    {
        puts("性别:1男2女");
        scanf(" %d", &new->list[new->number].sex);
        if (new->list[new->number].sex == 1 || new->list[new->number].sex == 2)
        {
            break;
        }
        puts("你选择了奇怪的性别，请重新输入");
    }

    puts("地址：");
    scanf(" %[^\n]", new->list[new->number].address); //在怎么把这个存进通讯录呢？
    new->number++;                                    //通讯录加1
    puts("添加信息成功");
}
//界面函数
void pr_chose()
{
    printf("**************\n");
    printf("**1.增加人员***\n");
    printf("**2.显示人员***\n");
    printf("**3.删除人员***\n");
    printf("**4.查找人员***\n");
    printf("**5.修改信息***\n");
    printf("**6.清空人员***\n");
    printf("**7.退出系统***\n");
    printf("**************\n");
}
//用户选择选择函数
int chose_num()
{
    int a = 0; //bug,输入字符会循环
    printf("请选择你想要的功能\n");
    scanf("%d", &a);
    return a;
}
