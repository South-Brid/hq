//文件属性或取函数
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
int main(int argc, char const *argv[])
{
    struct stat s;
    if (argc != 2)
    {
        printf("%s <filename>", argv[0]);
        return -1;
    }
    if (stat(argv[1], &s) < 0)
    {
        perror(argv[1]);
        return -1;
    }
    if ((s.st_mode & __S_IFMT) == __S_IFREG)
        putchar('_');
    if ((s.st_mode & __S_IFMT) == __S_IFDIR)
        putchar('d');
    if ((s.st_mode & __S_IFMT) == __S_IFCHR)
        putchar('c');
    if ((s.st_mode & __S_IFMT) == __S_IFIFO)
        putchar('p');
    if ((s.st_mode & __S_IFMT) == __S_IFBLK)
        putchar('b');
    if ((s.st_mode & __S_IFMT) == __S_IFSOCK)
        putchar('s');

    //文件权限
    if (s.st_mode & S_IRUSR)
    {
        putchar('r');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IWUSR)
    {
        putchar('w');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IXUSR)
    {
        putchar('x');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IRGRP)
    {
        putchar('r');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IWGRP)
    {
        putchar('w');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IXGRP)
    {
        putchar('x');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IROTH)
    {
        putchar('r');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IWOTH)
    {
        putchar('w');
    }
    else
    {

        putchar('-');
    }
    if (s.st_mode & S_IXOTH)
    {
        putchar('x');
    }
    else
    {

        putchar('-');
    }
    //链接数
    printf("%d ", s.st_nlink);

    struct passwd *uname = getpwuid(s.st_uid);
    printf("%s ", uname->pw_name);

    struct group *gname = getgrgid(s.st_gid);
    printf("%s ", gname->gr_name);

    printf("%ld ", s.st_size); //大小

    struct tm *f = localtime(&s.st_mtime);
    printf("%d月 %d日 %d:%d ", f->tm_mon + 1, f->tm_mday, f->tm_hour, f->tm_min);

    printf("%s",argv[1]);
    return 0;
}
