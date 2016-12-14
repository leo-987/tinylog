//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_TINYLOG_H
#define TINYLOG_TINYLOG_H

#include "LogStream.h"

class TinyLog {
public:
    TinyLog();

    ~TinyLog();


private:
    LogStream *pt_logstream_;
};


#endif //TINYLOG_TINYLOG_H
