//
// Created by ouyangliduo on 2016/12/13.
//

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

int32_t Buffer::Append()
{

}

void Buffer::Clear()
{

}

uint64_t Buffer::Size()
{

}

uint64_t Buffer::Capacity()
{

}