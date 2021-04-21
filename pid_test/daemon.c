#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i, fd;
    char* buf = "This is a Demon\n";

    pid = fork();
    if (pid < 0)
    {
        printf("Error fork\n");
        exit(1);
    }
    else if (pid > 0)
    {
        exit(0);
    }

    setsid();
    chdir("/");
    umask(0);

    for ( i = 0; i < getdtablesize(); i++)
    {
        close(i);
    }
    
    while (1)
    {
        if ((fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
        {
            printf("Open file error\n");
            exit(1);
        }
        write(fd, buf, strlen(buf));
        close(fd);
        sleep(5);
    }
    
    exit(0);
    
}
