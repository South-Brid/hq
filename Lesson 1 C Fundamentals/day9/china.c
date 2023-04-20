#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char ch;
    char arr[32] = "i love china";
    char *pa = arr;
    char *pb = arr + strlen(arr) - 1;
    char *pc = NULL;
    while (pa < pb)
    {
        ch = *pa;
        *pa = *pb;
        *pb = ch;
        pa++;
        pb--;
    }
    pa = pb = arr;
    while (*pb)
    {
        while (*pb == ' ')
        {
            pb++;
        }
        pa = pb;
        while (*pb != ' ' && *pb != '\0')
        {
            pb++;
        }
        pc = pb;
        pb--;
        while (pa < pb)
        {
            ch = *pa;
            *pa = *pb;
            *pb = ch;
            pa++;
            pb--;
        }
        pb = pc;
    }

    printf("%s", arr);
    return 0;
}
