//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_LOGSTREAM_H
#define TINYLOG_LOGSTREAM_H

#include <sys/time.h>

#include "Buffer.h"
#include "Utils.h"

class LogStream {
public:
    friend class TinyLog;

    LogStream();

    ~LogStream();

    void SwapBuffer();

    void WriteBuffer();

    void SetPrefix(const char *pt_file, int i_line, const char *pt_func, Utils::LogLevel e_log_level);

    LogStream& operator<<(const std::string &log);

private:
    Buffer *pt_front_buff_;

    Buffer *pt_back_buff_;

    int log_file_fd_;

    const char *pt_file_;

    int i_line_;

    const char *pt_func_;

    std::string str_log_level_;

    struct timeval tv_base_;

    struct tm *pt_tm_base_;
};


#endif //TINYLOG_LOGSTREAM_H
