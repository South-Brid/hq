#include <stdio.h>
int main(int argc, char const *argv[])
{
    char arr[20] = "a123x458";
    char *pa = arr;
    int brr[10] = {};
    int i=0;
    int num = 0;
    while (*pa)
    {
        if (*pa >= '0' && *pa <= '9')
        {
            num = num * 10 + *pa - 48;
        }
        else
        {

            num=0;
        }
        
        pa++;
    }

    return 0;
}
