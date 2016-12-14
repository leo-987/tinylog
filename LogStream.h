//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_LOGSTREAM_H
#define TINYLOG_LOGSTREAM_H

#include <Buffer.h>

class LogStream {
public:
    LogStream();

    ~LogStream();

private:
    Buffer *pt_front_buff_;
    Buffer *pt_back_buff_;
};


#endif //TINYLOG_LOGSTREAM_H
