//
// Created by ouyangliduo on 2016/12/13.
//

#include <time.h>

#include "TinyLog.h"
#include "Utils.h"
#include "Config.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;
bool g_already_swap = false;

static void *ThreadFunc(void *pt_arg)
{
    TinyLog *pt_tinylog = (TinyLog *)pt_arg;
    pt_tinylog->MainLoop();
}

TinyLog::TinyLog()
{
    pt_logstream_ = new LogStream();
    b_run_ = true;
    pthread_create(&tid_, NULL, ThreadFunc, this);
}

TinyLog::~TinyLog()
{
    b_run_ = false;
    pthread_join(tid_, NULL);
}

int32_t TinyLog::MainLoop()
{
    Utils::GetCurrentTime(&st_base_tv_, &pt_base_tm_);
    pthread_timestruc_t to;

    while (b_run_)
    {
        pthread_mutex_lock(&g_mutex);

        pthread_cond_timedwait(&g_cond, &g_mutex, &to);

        pthread_mutex_unlock(&g_mutex);
    }

    return 0;
}