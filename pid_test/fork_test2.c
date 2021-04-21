#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include<string.h>

int main(void)
{
    key_t key = ftok(".",'a');
    int shm_id = shmget(key,1024,IPC_CREAT|0666);
    pid_t pid = fork();
    if(pid == 0) {

        printf("son\n");
        char* p = shmat(shm_id,NULL,0);
        printf("&(*p) = %d\n", &(*p));
        //子进程写
        strncpy(p,"hahah",5);

    } else if(pid>0) {
        printf("father\n");
        char* p = shmat(shm_id,NULL,0);
        printf("&(*p) = %d\n", &(*p));
        sleep(1); 
        //父进程打印
        printf("read from share momery:%s\n",p);
    } else {
        printf("fork faided!\n");
        return -1;
    }
    return 0;
}