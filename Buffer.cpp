//
// Created by ouyangliduo on 2016/12/13.
//

#include <string.h>
#include <string>

#include "Buffer.h"

Buffer::Buffer(uint64_t l_capacity)
{
    pt_data_ = new char[l_capacity];
    l_size_ = 0;
    l_capacity_ = l_capacity;
}

Buffer::~Buffer()
{
    delete pt_data_;
}

/*
 * Append ref_log to buffer.
 * return value:
 * 0  : success
 * -1 : fail
 */
int32_t Buffer::TryAppend(const std::string &ref_log)
{
    if (l_size_ + ref_log.length() > l_capacity_)
    {
        return -1;
    }

    memcpy(pt_data_ + l_size_, ref_log.c_str(), ref_log.length());
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