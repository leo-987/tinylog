//
// Created by ouyangliduo on 2016/12/13.
//

#include <string.h>
#include <string>
#include <unistd.h>
#include <cerrno>

#include "Buffer.h"

Buffer::Buffer(uint64_t l_capacity)
{
    pt_data_ = new char[l_capacity];
    l_size_ = 0;
    l_capacity_ = l_capacity;
}

Buffer::~Buffer()
{
    // TODO
    delete pt_data_;
}

/*
 * Append time and log to buffer.
 * This function should be locked.
 * return value:
 * 0  : success
 * -1 : fail, buffer full
 */
int32_t Buffer::TryAppend(struct tm *pt_time, long u_sec, const char *pt_file, int i_line,
                          const char *pt_func, std::string &str_log_level, const char *pt_log)
{
    /*
     * date: 11 byte
     * time: 13 byte
     * line number: at most 5 byte
     * log level: 9 byte
     */
    std::string::size_type append_len = 24 + strlen(pt_file) + 5 + strlen(pt_func) + 9 + strlen(pt_log);

    if (append_len + l_size_ > l_capacity_)
    {
        return -1;
    }

    int n_append = sprintf(pt_data_ + l_size_, "%d-%02d-%02d %02d:%02d:%02d.%.03ld %s %d %s %s %s\n",
                           pt_time->tm_year + 1900, pt_time->tm_mon + 1, pt_time->tm_mday,
                           pt_time->tm_hour, pt_time->tm_min, pt_time->tm_sec, u_sec / 1000,
                           pt_file, i_line, pt_func, str_log_level.c_str(),
                           pt_log);

    if (n_append > 0)
    {
        l_size_ += n_append;
    }

    return 0;
}

void Buffer::Clear()
{
    l_size_ = 0;
}

uint64_t Buffer::Size()
{
    return l_size_;
}

uint64_t Buffer::Capacity()
{
    return l_capacity_;
}

// TODO: add epoll
int32_t Buffer::Flush(int fd)
{
    ssize_t n_write = 0;
    while ((n_write = write(fd, pt_data_ + n_write, l_size_ - n_write)) != 0)
    {
        if ((n_write < 0) && (errno != EINTR))
        {
            // error
            break;
        }
        else if (n_write == l_size_)
        {
            // All write
            break;
        }
        else if (n_write > 0)
        {
            // Half write
        }
    }

    // error
    if (n_write < 0)
        return -1;

    return 0;
}
