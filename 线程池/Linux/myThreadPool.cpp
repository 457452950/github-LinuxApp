#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>

using namespace std;

void *threadCallBack(void *arg);

class myThreadPool
{
public:
    struct Worker
    {
        pthread_t thread;
        myThreadPool *pool;
        int terminate;
    };

    struct Jobs
    {
        void (*func)(void *job);
        void *user_data;
    };

public:
    typedef queue<Jobs *> jobList;
    typedef vector<Worker *> workerList;

    jobList jobs;
    workerList workers;

public:
    pthread_cond_t jobs_cond;
    pthread_mutex_t jobs_mutex;

public:
    myThreadPool(int numberOfWorkers);
    ~myThreadPool();

    void push(struct Jobs *job);
};

myThreadPool::myThreadPool(int numberOfWorkers)
{
    if (numberOfWorkers < 1)
    {
        numberOfWorkers = 1;
    }

    // 初始化互斥量 jobs_cond
    jobs_cond = PTHREAD_COND_INITIALIZER;
    // 初始化互斥锁 jobs_mutex
    jobs_mutex = PTHREAD_MUTEX_INITIALIZER;

    // 启动线程
    for (int i = 0; i < numberOfWorkers; i++)
    {
        struct Worker *worker = new Worker;
        if (worker == nullptr)
        {
            perror("new");
            return;
        }
        worker->pool = this;

        int ret = pthread_create(&worker->thread, NULL, threadCallBack, worker);
        if (ret)
        {
            perror("pthread_create");
            free(worker);
            return;
        }

        workers.push_back(worker);
    }
}

myThreadPool::~myThreadPool()
{
    for (auto worker : workers)
    {
        worker->terminate = 1;
    }

    pthread_mutex_lock(&jobs_mutex);
    pthread_cond_broadcast(&jobs_cond);
    pthread_mutex_unlock(&jobs_mutex);
}

void myThreadPool::push(struct Jobs *job)
{
    pthread_mutex_lock(&jobs_mutex);
    printf("add\n");
    jobs.push(job);
    pthread_cond_signal(&jobs_cond);
    pthread_mutex_unlock(&jobs_mutex);
}

void *threadCallBack(void *arg)
{
    printf("start of thread\n");
    myThreadPool::Worker *worker = (myThreadPool::Worker *)arg;

    while (1)
    {
        pthread_mutex_lock(&worker->pool->jobs_mutex);

        while (worker->pool->jobs.empty())
        {
            printf("empty\n");
            if (worker->terminate)
            {
                printf("terminate\n");
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

        struct myThreadPool::Jobs *job = worker->pool->jobs.front();
        worker->pool->jobs.pop();
        printf("size = %u\n", worker->pool->jobs.size());

        pthread_mutex_unlock(&worker->pool->jobs_mutex);

        job->func(job->user_data);
    }

    printf("end of thread\n");
    free(worker);
    pthread_exit(NULL);
}

void myfunc(void *arg)
{
    int i = *((int *)arg);
    printf(" data = %d, & = %d   .\n", i, (int *)arg);
}

int main(void)
{
    int number = 5;
    myThreadPool pool = myThreadPool(number);

    while (1)
    {
        if (getchar())
        {
            for (int i = 0; i < 10 * number; i++)
            {
                struct myThreadPool::Jobs *job = new (myThreadPool::Jobs);
                job->func = myfunc;
                int d1 = i;
                job->user_data = (void *)&d1;
                pool.push(job);
            }
        }
    }

    return 0;
}