#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

#define LL_ADD(item, list)     \
    do                         \
    {                          \
        item->prev = NULL;     \
        item->next = list;     \
        if (list != NULL)      \
            list->prev = item; \
        list = item;           \
    } while (0)

#define LL_REMOVE(item, list)              \
    do                                     \
    {                                      \
        if (item->prev != NULL)            \
            item->prev->next = item->next; \
        if (item->next != NULL)            \
            item->next->prev = item->prev; \
        if (list == item)                  \
            list = item->next;             \
        item->prev = item->next = NULL;    \
    } while (0)

struct NWORKER
{
    pthread_t thread;
    struct NMANAGER *pool;
    int terminate;

    struct NWORKER *prev;
    struct NWORKER *next;
};

struct NJOB
{
    void (*func)(void *job);
    void *user_data;

    struct NJOB *prev;
    struct NJOB *next;
};

struct NMANAGER
{
    struct NWORKER *workers;
    struct NJOB *jobs;

    pthread_cond_t jobs_cond;
    pthread_mutex_t jobs_mutex;
};

typedef struct NMANAGER nThreadPool;

int numberOfJob = 0;

static void *nThreadCallBack(void *arg)
{
    struct NWORKER *worker = (struct NWORKER *)arg;

    while (1)
    {
        // pthread_cond_wait中会解锁，运行完毕后会加锁
        pthread_mutex_lock(&worker->pool->jobs_mutex);
        while (worker->pool->jobs == NULL)
        {
            printf("jobs:%d \n", numberOfJob);
            printf("worker->pool->jobs == NULL\n");
            if (worker->terminate)
            {
                printf("worker->terminate\n");
                break;
            }

            pthread_cond_wait(&worker->pool->jobs_cond, &worker->pool->jobs_mutex);
            printf("wake up\n");
        }

        if (worker->terminate)
        {
            pthread_mutex_unlock(&worker->pool->jobs_mutex);
            printf("worker->terminate\n");
            break;
        }

        struct NJOB *job = worker->pool->jobs;
        LL_REMOVE(job, worker->pool->jobs);

        printf("remove jobs:%d \n", --numberOfJob);
        pthread_mutex_unlock(&worker->pool->jobs_mutex);

        printf("job->func()\n");
        job->func(job->user_data);
    }

    printf("end of thread\n");
    free(worker);
    pthread_exit(NULL);
}

// Thread Pool Create
int nThreadPoolCreate(nThreadPool *pool, int numberWokers)
{
    if (numberWokers < 1)
    {
        numberWokers = 1;
    }
    if (pool == NULL)
    {
        printf("pool is NULL");
        return -1;
    }
    memset(pool, 0, sizeof(nThreadPool));

    // 创建互斥量 blank_cond
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&pool->jobs_cond, &blank_cond, sizeof(pthread_cond_t));

    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&pool->jobs_mutex, &blank_mutex, sizeof(pthread_mutex_t));

    int i = 0;
    for (i = 0; i < numberWokers; ++i)
    {
        struct NWORKER *worker = (struct NWORKER *)malloc(sizeof(struct NWORKER));
        if (worker == NULL)
        {
            perror("malloc");
            return -2;
        }
        memset(worker, 0, sizeof(struct NWORKER));
        worker->pool = pool;

        int ret = pthread_create(&worker->thread, NULL, nThreadCallBack, worker);
        printf("pthread_create\n");
        if (ret)
        {
            perror("pthread_create");
            free(worker);
            return -3;
        }

        LL_ADD(worker, pool->workers);
    }

    return 1;
}

void nThreadPoolPush(nThreadPool *pool, struct NJOB *job)
{
    pthread_mutex_lock(&pool->jobs_mutex);
    numberOfJob++;
    printf("add jobs:%d \n", numberOfJob);
    LL_ADD(job, pool->jobs);
    pthread_cond_signal(&pool->jobs_cond);

    pthread_mutex_unlock(&pool->jobs_mutex);
}

int nThreadPoolDestroy(nThreadPool *pool)
{
    printf("nThreadPoolDestroy");
    printf("jobs:%d \n", numberOfJob);
    struct NWORKER *worker = NULL;
    for (worker = pool->workers; worker != NULL; worker = worker->next)
    {
        // pthread_join(worker->thread, NULL);
        pthread_detach(worker->thread);
        worker->terminate = 1;
    }

    pthread_mutex_lock(&pool->jobs_mutex);
    pthread_cond_broadcast(&pool->jobs_cond);
    pthread_mutex_unlock(&pool->jobs_mutex);
}

void myfunc(void *arg)
{
    int i = *((int *)arg);
    printf(" data = %d, & = %d   .\n", i, (int *)arg);
}

int main()
{
    printf("main\n");
    int number = 5;
    nThreadPool *pool = (nThreadPool *)malloc(sizeof(struct NMANAGER));
    int ret = nThreadPoolCreate(pool, number);
    if (ret < 0)
    {
        printf("error");
        return -1;
    }

    // int d[] = {0, 1, 2};
    int d1 = 0;
    int d2 = 1;
    for (int i = 0; i < number; i++)
    {
        struct NJOB *job = (struct NJOB *)malloc(sizeof(struct NJOB));
        job->func = myfunc;
        job->user_data = (void *)&d1;
        nThreadPoolPush(pool, job);
    }

    unsigned int n = 1410065407;
    while (n--)
    {
        /* code */
        // printf("n");
        ;
    }

    while (1)
    {
        /* code */
        // printf("n");
        ;
    }
    nThreadPoolDestroy(pool);

    n = 999999;
    while (n--)
    {
        /* code */
        // printf("n");
        ;
    }
    return 0;
}
