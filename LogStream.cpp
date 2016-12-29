//
// Created by ouyangliduo on 2016/12/13.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "LogStream.h"
#include "Config.h"

extern pthread_mutex_t g_mutex;
extern pthread_cond_t g_cond;
extern bool g_already_swap;

LogStream::LogStream()
{
    log_file_fd_ = open(LOG_PATH, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    pt_front_buff_ = new Buffer(BUFFER_SIZE);
    pt_back_buff_  = new Buffer(BUFFER_SIZE);

    Utils::GetCurrentTime(&tv_base_, &pt_tm_base_);
}

LogStream::~LogStream()
{
    delete(pt_front_buff_);
    delete(pt_back_buff_);

    close(log_file_fd_);
}

/*
 * Swap front buffer and back buffer.
 * This function should be locked.
 */
void LogStream::SwapBuffer()
{
    Buffer *pt_tmp = pt_front_buff_;
    pt_front_buff_ = pt_back_buff_;
    pt_back_buff_ = pt_tmp;
}

/*
 * Write buffer data to log file.
 * This function should be locked.
 */
void LogStream::WriteBuffer()
{
    pt_back_buff_->Flush(log_file_fd_);
    pt_back_buff_->Clear();
}

inline
void LogStream::SetPrefix(const char *pt_file, int i_line, const char *pt_func, Utils::LogLevel e_log_level)
{
    pt_file_ = pt_file;
    i_line_  = i_line;
    pt_func_ = pt_func;

    switch (e_log_level)
    {
        case Utils::DEBUG  : str_log_level_ = "[DEBUG  ]"; break;
        case Utils::INFO   : str_log_level_ = "[INFO   ]"; break;
        case Utils::WARNING: str_log_level_ = "[WARNING]"; break;
        case Utils::ERROR  : str_log_level_ = "[ERROR  ]"; break;
        case Utils::FATAL  : str_log_level_ = "[FATAL  ]"; break;
        default: str_log_level_ = "[INFO   ]"; break;
    }
}

LogStream& LogStream::operator<<(const std::string &log)
{
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);

    if (tv_now.tv_sec != tv_base_.tv_sec)
    {
        int new_sec = pt_tm_base_->tm_sec + int(tv_now.tv_sec - tv_base_.tv_sec);
        if (new_sec >= 60)
        {
            pt_tm_base_->tm_sec = new_sec % 60;
            int new_min = pt_tm_base_->tm_min + new_sec / 60;
            if (new_min >= 60)
            {
                pt_tm_base_->tm_min = new_min % 60;
                int new_hour = pt_tm_base_->tm_hour + new_min / 60;
                if (new_hour >= 24)
                {
                    Utils::GetCurrentTime(&tv_base_, &pt_tm_base_);
                }
                else
                {
                    pt_tm_base_->tm_mday = new_hour;
                }
            }
            else
            {
                pt_tm_base_->tm_min = new_min;
            }
        }
        else
        {
            pt_tm_base_->tm_sec = new_sec;
        }
    }

    tv_base_ = tv_now;

    pthread_mutex_lock(&g_mutex);

    if (pt_front_buff_->TryAppend(pt_tm_base_, (long)tv_base_.tv_usec, pt_file_, i_line_, pt_func_, str_log_level_, log) < 0)
    {
        SwapBuffer();
        g_already_swap = true;
        pt_front_buff_->TryAppend(pt_tm_base_, (long)tv_base_.tv_usec, pt_file_, i_line_, pt_func_, str_log_level_, log);
    }

    pthread_cond_signal(&g_cond);

    pthread_mutex_unlock(&g_mutex);

    return *this;
}
