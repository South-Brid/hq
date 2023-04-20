#include <stdio.h>
#include <stdlib.h>

//描述顺序栈的结构体
typedef int datatype_t;
typedef struct 
{
    datatype_t *data;
    int top;
    int len;
}stack_t,*stack_p; 

//1.创建空的顺序栈
stack_p createStack(int lenth);
//2.入栈    p 
int pushStack(stack_p p,datatype_t data);
//3.判断栈是否满  1满  0未满
int isFullStack(stack_p p);
//4.出栈
datatype_t outStack(stack_p p);
//5.判断栈是否为空 1空  0非空
int isEmptyStack(stack_p p);
//6.计算栈长度(入栈数据的个数)
int lenStack(stack_p p);
//7.获取栈顶数据
datatype_t topStack(stack_p p);
//8.清空栈
void clearStack(stack_p p);
//9.销毁栈
void  destoryStack(stack_p *sp);






//1.创建空的顺序栈
stack_p createStack(int lenth)
{
    //1.开辟一个结构体空间保存栈的信息
    stack_p p=(stack_p )malloc(sizeof(stack_t));
    if(NULL == p)
    {
        printf("malloc err.\n");
        return NULL;
    }
    //2.初始结构体
    p->data=(datatype_t *)malloc(sizeof(datatype_t)*lenth);
    if(NULL == p->data)
    {
        printf("malloc stack err.\n");
        free(p);
        return NULL;
    }

    p->top=-1;//空栈
    p->len=lenth;
    return p;
}
//3.判断栈是否满  1满  0未满
int isFullStack(stack_p p)
{
    return p->top+1 == p->len;
}
//2.入栈    p 
int pushStack(stack_p p,datatype_t data)
{
    if(isFullStack(p))
    {
        printf("stack Full.\n");
        return -1;
    }
    p->top++;
    p->data[p->top]=data;
    return 0;
}
//5.判断栈是否为空 1空  0非空
int isEmptyStack(stack_p p)
{
    return p->top==-1;
}
//4.出栈
datatype_t outStack(stack_p p)
{
    if(isEmptyStack(p))
    {
        printf("stack empty.\n");
        return -1;
    }   
    return p->data[p->top--];
}

//6.计算栈长度(入栈数据的个数)
int lenStack(stack_p p)
{
    return p->top+1;
}
//7.获取栈顶数据
datatype_t topStack(stack_p p)
{
    if(isEmptyStack(p))
    {
        printf("empty err.\n");
        return -1;
    }
    return p->data[p->top];
}
//8.清空栈
void clearStack(stack_p p)
{
    p->top=-1;
}
//9.销毁栈
void  destoryStack(stack_p *sp)
{
     free((*sp)->data);
     free(*sp);
     *sp=NULL;
}

int main(int argc, char const *argv[])
{
    stack_p p=createStack(6);
    int a=6;
    while(!isFullStack(p))
    {
        pushStack(p,a++);
    }
    while(!isEmptyStack(p))
    {
        printf("%d ",outStack(p));
    }
    putchar(10);
    printf("p->top:%d\n",p->top);

    destoryStack(&p);
    printf("%p\n",p);
    return 0;
}

