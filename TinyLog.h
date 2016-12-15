//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_TINYLOG_H
#define TINYLOG_TINYLOG_H

#include <pthread.h>

#include "LogStream.h"

class TinyLog {
public:
    TinyLog();

    ~TinyLog();

    int32_t MainLoop();

private:
    LogStream *pt_logstream_;

    pthread_t tid_;

    bool b_run_;

    struct timeval st_base_tv_;

    struct tm *pt_base_tm_;
};


#endif //TINYLOG_TINYLOG_H
