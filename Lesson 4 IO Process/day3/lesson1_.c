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
    //第一部分
    if (stat(argv[1], &s) < 0)
    //参数定义变量，返回值定义指针
    /*
    功能：使用stat结构体将文件得属性调出来
    
    参数：
    第一个参数：文件路径
    第二个参数：stat类型得结构体指针
    */
    {
        perror(argv[1]);
        return -1;
    }

    printf("%ld ",s.st_size);//大小

    //第二部分：链接数
    printf("%d ",s.st_nlink);

    //第三部分：用户名和组名
    //需要将用户ID和组ID转换成用户名和组名
    //getpwuid()用户名
    struct passwd *uname = getpwuid(s.st_uid);
    printf("%s ", uname->pw_name);
    //getgrgid()组名
    struct group *gname = getgrgid(s.st_gid);
    printf("%s ", gname->gr_name);
    //第四部分：时间
    //st_mtime,通过localtime进行转换成时间格式
    struct tm *f = localtime(&s.st_mtime);
    printf("%d月 %d日 %d:%d ", f->tm_mon + 1, f->tm_mday, f->tm_hour, f->tm_min);
    //第五部分：判断文件类型
    if ((s.st_mode & __S_IFMT) == __S_IFREG)
        //如果s结构体下的st_mode&S_IFMT==S_IFREG 就证明是普通文件
        putchar('_');
    if ((s.st_mode & __S_IFMT) == __S_IFDIR)
        //如果s结构体下的st_mode&S_IFMT==S_IFDIR 就证明是目录文件
        putchar('d');
    if ((s.st_mode & __S_IFMT) == __S_IFCHR)
        putchar('c');
    if ((s.st_mode & __S_IFMT) == __S_IFIFO)
        putchar('p');
    if ((s.st_mode & __S_IFMT) == __S_IFBLK)
        putchar('b');
    if ((s.st_mode & __S_IFMT) == __S_IFSOCK)
        putchar('s');

    //第六部分：文件权限
    //判断用户读
    /*
    优化版程序    
    */
    char buf[4]="rwx-";
    for (int i = 0; i < 9; i++)
    {
        printf("%c",(s.st_mode&(0400>>i)?buf[i%3]:buf[3]));//
    }
    return 0;
}
