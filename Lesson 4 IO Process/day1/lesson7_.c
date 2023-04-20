#include <stdio.h>
#include <string.h>
void fg();
int main(int argc, char const *argv[])
{
    fg();
    return 0;
}
void fg()
{
    FILE*fp;
    fp=fopen("text.c","r");
    if (fopen == NULL)
    {
        perror("text.c:");
        return;
    }
    char ch;
    int num=0;
    while ((ch=fgetc(fp))!=EOF)
    {
        if(ch == '\n')
        num++;
    }
    printf("%d ",num);
    
}