#include "iostream"
#include "thread"
#include "vector"
#include "signal.h"
#include "memory.h"
using namespace std;

// killall -15 epoll_test

struct st_message
{
    int mesgid;
    char message[1024];
} ;


int mesgid = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
vector<struct st_message> vcache;


void* outcache(void* argc);
void incache(int sig);


int main(void)
{
    signal(15, incache);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);


    pthread_t th1, th2, th3;

    pthread_create(&th1, NULL, outcache, NULL);
    pthread_create(&th2, NULL, outcache, NULL);
    pthread_create(&th3, NULL, outcache, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    return 0;
}




void* outcache(void* argc)
{
    struct st_message stmesg;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (vcache.empty())
        {
            pthread_cond_wait(&cond, &mutex);
        }

        memcpy(&stmesg, &vcache[0], sizeof(struct st_message));
        vcache.erase(vcache.begin());

        pthread_mutex_unlock(&mutex);

        printf("phid = %ld, mesgid = %d\n", pthread_self(), stmesg.mesgid);
        
    }
}

void incache(int sig)
{
    struct st_message stmesg;
    memset(&stmesg, 0, sizeof(struct st_message));
    
    pthread_mutex_lock(&mutex);

    stmesg.mesgid = mesgid++;    vcache.push_back(stmesg);
    stmesg.mesgid = mesgid++;    vcache.push_back(stmesg);
    stmesg.mesgid = mesgid++;    vcache.push_back(stmesg);
    stmesg.mesgid = mesgid++;    vcache.push_back(stmesg);
    stmesg.mesgid = mesgid++;    vcache.push_back(stmesg);

    pthread_mutex_unlock(&mutex);

    pthread_cond_broadcast(&cond);
}