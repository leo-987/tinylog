//
// Created by ouyangliduo on 2016/12/13.
//

#ifndef TINYLOG_BUFFER_H
#define TINYLOG_BUFFER_H


#include <cstdint>
#include <string>

class Buffer {
public:
    Buffer(uint64_t l_capacity);

    ~Buffer();

    int32_t TryAppend(const std::string &ref_log);

    void Clear();

    uint64_t Size();

    uint64_t Capacity();

    int32_t Flush(int fd);

private:
    char *pt_data_;

    uint64_t l_size_;

    uint64_t l_capacity_;
};


#endif //TINYLOG_BUFFER_H
