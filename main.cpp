#include <iostream>

#include "TinyLog.h"

using namespace std;

void *WorkThread1(void *arg)
{
    string log = "hello world";

    cerr << "start time: " << Utils::GetCurrentTime() << endl;

    for (int i = 0; i < 10000000; i++)
    {
        LOG_INFO << log;
    }

    cerr << "end time: " << Utils::GetCurrentTime() << endl;
}

void *WorkThread2(void *arg)
{
    string log = "hello world";

    cerr << "start time: " << Utils::GetCurrentTime() << endl;

    for (int i = 0; i < 10000000; i++)
    {
        LOG_INFO << log;
    }

    cerr << "end time: " << Utils::GetCurrentTime() << endl;
}

int main()
{
    g_tinylog.SetLogLevel(Utils::INFO);
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, WorkThread1, NULL);
    pthread_create(&tid2, NULL, WorkThread2, NULL);


    cin.get();

    return 0;
}