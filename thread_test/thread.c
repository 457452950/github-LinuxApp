#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <wait.h>

#define THREAD_NUMBER 3
#define REPEAT_NUMBER 5
#define DELAY_TIME_LEVELS 10.0

pthread_mutex_t mutex;

// void *thrd_func(void* arg)
// {
//     int thrd_num = (int)arg;
//     int delay_time = 0;
//     int count = 0;

//     printf("Thread %d is starting\n", thrd_num);
//     for ( count = 0; count < REPEAT_NUMBER; count++)
//     {
//         delay_time = (int) (rand()* DELAY_TIME_LEVELS/(RAND_MAX)) + 1;
//         sleep(delay_time);  
//         printf("\tThread %d: job %d delay = %d\n", thrd_num, count, delay_time);
//     }
//     printf("Thread %d finished\n", thrd_num);
//     pthread_exit(NULL);
   
// }

int n = 0;

void * thrd_fun1(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("func1 runing, thread : %d\n", (int)arg);
        printf("n = %d", n++);
        pthread_mutex_unlock(&mutex);
    }
    
}
void * thrd_fun2(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("func2 runing, thread : %d\n", (int)arg);
        printf("n = %d", n++);
        pthread_mutex_unlock(&mutex);
    }
    
}
void * thrd_fun3(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("func3 runing, thread : %d\n", (int)arg);
        printf("n = %d", n++);
        pthread_mutex_unlock(&mutex);
    }
    
}
int main(void)
{
    pthread_t thread[THREAD_NUMBER];
    int no = 0, res;
    void * thrd_ret;

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    // for (no = 0; no < THREAD_NUMBER; no++)
    // {
    //     res = pthread_create(&thread[no], NULL, thrd_fun1, (void*)no);
    //     if (res != 0)
    //     {
    //         printf("Create thread %d failed\n",no);
    //         exit(res);
    //     }
         
    // }

    {
         res = pthread_create(&thread[no], NULL, thrd_fun1, (void*)no++);
        if (res != 0)
        {
            printf("Create thread %d failed\n",no);
            exit(res);
        }
         res = pthread_create(&thread[no], NULL, thrd_fun2, (void*)no++);
        if (res != 0)
        {
            printf("Create thread %d failed\n",no);
            exit(res);
        }
         res = pthread_create(&thread[no], NULL, thrd_fun3, (void*)no);
        if (res != 0)
        {
            printf("Create thread %d failed\n",no);
            exit(res);
        }
    }
    
    printf("Create threads success\nWaiting for threads to finish...\n");
    
    for ( no = 0; no < THREAD_NUMBER; no++)
    {
        res = pthread_join(thread[no], &thrd_ret);
        if (!res)
        {
            printf("THread %d joined\n", no);
        }
        else
            printf("Thread %d join failed\n", no);
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}