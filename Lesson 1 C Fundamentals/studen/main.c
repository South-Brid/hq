#include <stdio.h>
#include <stdlib.h>
#define max 1000
//结构体区
typedef struct students
{
    int st_num;           //学号
    float chiness_result; //汉语
    float match_result;   //数学
    float english_result; //英语
    float ping_result;    //平均分
} stu;

typedef struct school
{
    int sc_num; //记录人数
    stu list[max];
} sch;
//函数声明区
void jie_mian();                 //打印界面函数
int usr_chose();                //用户选择函数
void intput_result(sch *pa);     //成绩录入
void find_result(sch *pb);       //列出成绩表
void jisuanping_result(sch *pc); //计算平均分
void pingresult_pai(sch *pd);    //平均分排序
int find_number_result(sch *pd); //按照学号查询成绩
void clear();                    //清屏

int main(int argc, char const *argv[])
{
    jie_mian();
    usr_chose();
    return 0;
}
//请屏命令
void clear()
{
    system("clear");
    printf("请输入命令 = ");
}

//按照平均分进行排序
void pingresult_pai(sch *pd)
{
    int i;
    int j;
    sch mid;
    for (j = 0; j < pd->sc_num - 1; j++)
    {
        for (i = 0; i < pd->sc_num - j - 1; i++)
        {
            if (pd->list[i].ping_result < pd->list[i + 1].ping_result)
            {
                mid.list[i] = pd->list[i];
                pd->list[i] = pd->list[i + 1];
                pd->list[i + 1] = mid.list[i];
            }
        }
    }
    puts("完成排序。请使用命令L查看");
}
//按照学生学号查询成绩
int find_number_result(sch *pd)
{
    int x;
    puts("输入要查询的学生学号");
    scanf("%d", &x);
    int i;
    for (i = 0; i < pd->sc_num; i++)
    {

        if (x == pd->list[i].st_num)
        {
            puts("学号   语文   数学   外语   平均分");
            printf("%d      %.1f  %.1f  %.1f  %.1f\n",
                   pd->list[i].st_num,
                   pd->list[i].chiness_result,
                   pd->list[i].english_result,
                   pd->list[i].match_result,
                   pd->list[i].ping_result);
            printf("请输入命令 = ");
            return 1;
        }
    }
    puts("未查找到信息");
    printf("请输入命令 = ");
    return 1;
}
//计算平均分
void jisuanping_result(sch *pc)
{
    int i = 0;
    for (i = 0; i < pc->sc_num; i++)
    {
        pc->list[i].ping_result =
            (pc->list[i].chiness_result +
             pc->list[i].english_result +
             pc->list[i].match_result) /
            3;
    }
    puts("平均分已经计算");
    printf("请输入命令 = ");
}
//列出成绩表函数
void find_result(sch *pb)
{
    if (pb->sc_num == 0)
    {
        puts("成绩列表为空！请先使用T录入学生成绩");
    }
    else
    {
        int i;
        puts("学生的成绩如下：");
        puts("学号   语文   数学   外语   平均分");
        for (i = 0; i < pb->sc_num; i++)
        {
            printf("%d      %.1f  %.1f  %.1f  %.1f\n",
                   pb->list[i].st_num,
                   pb->list[i].chiness_result,
                   pb->list[i].english_result,
                   pb->list[i].match_result,
                   pb->list[i].ping_result);
        }
    }
    printf("请输入命令 = ");
}

//成绩录入函数
void intput_result(sch *pa)
{
    int x_num;
    //创建变量存放输入学生人数
    puts("请输入学生人数：");
    scanf("%d", &x_num);
    int i;
    int x = 0;
    //记录第二个循环次数
    static int j = 0;
    //创建标记
    printf("请输入%d名同学的三门成绩:\n", x_num);
    puts("学号 语文 数学 外语");
    if (j == 0)
    {
        for (i = 0; i < x_num; i++)
        {
            scanf("%d %f %f %f",
                  &pa->list[i].st_num,
                  &pa->list[i].chiness_result,
                  &pa->list[i].match_result,
                  &pa->list[i].english_result);
            pa->sc_num++;
            j++; //让人数加1
        }
    }
    else
    {
        for (i = j; i < j + x_num; i++)
        {
            scanf("%d %f %f %f",
                  &pa->list[i].st_num,
                  &pa->list[i].chiness_result,
                  &pa->list[i].match_result,
                  &pa->list[i].english_result);
            pa->sc_num++;
            x++; //标记循环次数
        }
        j = j + x;
    }

    printf("请输入命令 = ");
}

//用户选择函数
int usr_chose()
{
    sch students_list;
    while (1)
    {
        char c;
        //创建变量用于给用户选择
        scanf("%c", &c);
        switch (c)
        {
        case 'H':
            jie_mian();
            break;
        case 'T':
            intput_result(&students_list);
            break;
        case 'A':
            jisuanping_result(&students_list);
            break;
        case 'L':
            find_result(&students_list);
            break;
        case 'P':
            pingresult_pai(&students_list);
            break;
        case 'S':
            find_number_result(&students_list);
            break;
        case 'C':
            clear();
            break;
        case 'Q':
            return 0;
        default:
            break;
        }
    }
}

//打印界面函数
void jie_mian()
{
    puts("*************************************");
    puts("*       学生管理系统--帮助菜单      *");
    puts("*************************************");
    puts("*    H = 显示帮助菜单               *");
    puts("*    T = 成绩录入                   *");
    puts("*    A = 计算学生平均分             *");
    puts("*    L = 列出成绩单                 *");
    puts("*    P = 按照平均成绩由高到底排序   *");
    puts("*    S = 按学号查询学生成绩         *");
    puts("*    C = 清屏                       *");
    puts("*    Q = 推出系统                   *");
    puts("*************************************");
    puts("*  Copyright <c> 2023.03.22 by sqt  *");
    puts("*************************************");

    printf("请输入命令 = ");
}
