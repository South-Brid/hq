#include <stdio.h>
#include <string.h>
struct students
{
    char name[10];
    int age;
};

int main(int argc, char const *argv[])
{
    // char arr[15] = "hellofffff";
    // char brr[10] = "world";
    // strncpy(arr, brr, 5);
    // printf("%s \n", arr);
    // int i;
    // for (i = 0; i < 15; i++)
    //     printf("%d ", arr[i]);
    // char crr[100] = "zello";
    // char drr[100] = "aorld";
    // printf("%d",strcmp(crr, drr));
    struct students lili = {"lili", 18};
    struct students liuxing = {
        .name = "lixing",
        .age = 19};
    scanf("%s %d",lili.name,&lili.age);
    printf("%s\n", lili.name);
    printf("%d\n", lili.age);

    printf("%s\n", liuxing.name);
    printf("%d\n", liuxing.age);
    return 0;
}
