#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void handler(int sig)
{
    printf("chaojiwudidashuaige\n");
}

int main(int argc, char const *argv[])
{
    struct sigaction act;
    sigaction(SIGALRM,NULL,&act);
    act.sa_handler=handler;
    sigaction(SIGALRM,&act,NULL);

    char buf[32];
    while (1)
    {
        alarm(3);
        if(fgets(buf,sizeof(buf),stdin)==NULL)
        {
            perror("fgets err.");
            continue;
        }
        printf("%s",buf);
    }
    return 0;
}
