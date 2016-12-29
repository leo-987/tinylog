//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_TINYLOG_H
#define TINYLOG_TINYLOG_H

#include <pthread.h>

#include "LogStream.h"
#include "Utils.h"

class TinyLog {
public:
    static TinyLog& GetInstance()
    {
        static TinyLog instance;
        return instance;
    }

    TinyLog();

    ~TinyLog();

    int32_t MainLoop();

    void SetLogLevel(Utils::LogLevel e_log_level);

    Utils::LogLevel GetLogLevel();

    LogStream& GetLogStream(const char *pt_file, int i_line, const char *pt_func, Utils::LogLevel e_log_level);

private:
    TinyLog(TinyLog const &);

    void operator=(TinyLog const &);

    LogStream *pt_logstream_;

    pthread_t tid_;

    bool b_run_;

    Utils::LogLevel e_log_level_;
};

#define g_tinylog (TinyLog::GetInstance())

#define LOG_INFO if (g_tinylog.GetLogLevel() <= Utils::INFO)\
        g_tinylog.GetLogStream(__FILE__, __LINE__, __func__, Utils::INFO)

#define LOG_WARNING if (g_tinylog.GetLogLevel() <= Utils::WARNING) \
        g_tinylog.GetLogStream(__FILE__, __LINE__, __func__, Utils::WARNING)

#endif //TINYLOG_TINYLOG_H
