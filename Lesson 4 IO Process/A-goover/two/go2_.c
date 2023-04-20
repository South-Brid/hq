//fseek调用
//向文件指定位置插入字符
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "a+"); //此处用a就不可以,fseek在a和a+模式下是无法使用得
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    fseek(fp, 10, SEEK_SET);
    fputc('c', fp);
    fseek(fp, 10, SEEK_SET);
    fputc('c', fp);
    printf("%ld", ftell(fp));
    return 0;
}
