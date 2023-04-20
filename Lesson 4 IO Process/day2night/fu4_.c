#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[10] = "helloworld";
    char brr[10] = "";
    fp = fopen("fu1.txt", "w+");
    if (fp == NULL)
    {
        perror("fu1.txt");
        return -1;
    }
    fseek(fp,9,SEEK_SET);
    fputs("aaaaaaaaaaaaa",fp);
    fseek(fp,10,SEEK_CUR);
    fputs("bbbbbbbbbbbb",fp);
    fclose(fp);
    return 0;
}
