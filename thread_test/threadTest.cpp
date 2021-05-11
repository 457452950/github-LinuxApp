#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;


void* func1(void* arg);
void* func2(void* arg);
void* func3(void* arg);
void* func4(void* arg);
void* func5(void* arg);



int main(void)
{
    pthread_t p1, p2, p3, p4, p5;

    long i = 10;
    void* ptr = (void*)i;

    if (pthread_create(&p1, NULL, func1, ptr) != 0)
    {
        cout << "创建线程1失败" << endl;
    }
    if (pthread_create(&p2, NULL, func2, NULL) != 0)
    {
        cout << "创建线程2失败" << endl;
    }
    if (pthread_create(&p3, NULL, func3, NULL) != 0)
    {
        cout << "创建线程3失败" << endl;
    }
    if (pthread_create(&p4, NULL, func4, NULL) != 0)
    {
        cout << "创建线程4失败" << endl;
    }
    if (pthread_create(&p5, NULL, func5, NULL) != 0)
    {
        cout << "创建线程5失败" << endl;
    }
    
    long n = 0;
    pthread_join(p1, (void**)&n);
    cout << "线程1完毕, retVal:" << n << endl;
    pthread_join(p2, NULL);
    cout << "线程2完毕" << endl;
    pthread_join(p3, NULL);
    cout << "线程3完毕" << endl;
    pthread_join(p4, NULL);
    cout << "线程4完毕" << endl;
    pthread_join(p5, NULL);
    cout << "线程5完毕" << endl;



    // while (1)
    // {
    //     ;
    // }
    return 0;
    
}


void* func1(void* arg)
{
    cout << "线程1开始" << endl;
    long i = (long)arg;
    cout << i << endl;
    sleep(10);
    i += 10;
    return (void*)i;
}
void* func2(void* arg)
{
    cout << "线程2开始" << endl;
    sleep(10);
    return 0;
}
void* func3(void* arg)
{
    cout << "线程3开始" << endl;
    sleep(10);
    return 0;
}
void* func4(void* arg)
{
    cout << "线程4开始" << endl;
    sleep(10);
    return 0;
}
void* func5(void* arg)
{
    cout << "线程5开始" << endl;
    sleep(10);
    return 0;
}