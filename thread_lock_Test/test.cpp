#include <iostream>
#include <thread>
using namespace std;

int PubNum = 0;
pthread_mutex_t mux1;

void* threadfunc(void* argv);




int main(int argc, char** argv)
{
    pthread_t th1, th2;
    pthread_mutex_init(&mux1, NULL);

    pthread_create(&th1, NULL, threadfunc, (void*)1);

    pthread_create(&th2, NULL, threadfunc, (void*)2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mux1);

    return 0;
}

void* threadfunc(void* argv)
{
    while (1)
    {
        pthread_mutex_lock(&mux1);

        PubNum += 1;
        cout << (long)argv ;
        cout << " PubNum = " << PubNum << endl;
        
        pthread_mutex_unlock(&mux1);
    }
    
}


