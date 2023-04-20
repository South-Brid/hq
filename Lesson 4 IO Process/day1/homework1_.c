#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[] = ",hello world\n";
    char brr[100] = {0};
    fp = fopen("test.txt", "a+");
    if (fopen == NULL)
    {
        perror("text.txt:");
        return -1;
    }
    int i = 1;
    while (fgets(brr, 100, fp) != NULL)
    {
        if (brr[strlen(brr)-1] == '\n')
        {
            i++;
        }
    }
    while (1)
    {
        fprintf(fp,"%d",i++);
        fputs(arr, fp); //向文件写入helloworld
        fflush(fp);
        sleep(1);
    }
    fclose(fp);
    return 0;
}
