//
// Created by ouyangliduo on 2017/1/7.
//

#ifndef TINYLOG_FREELOCKQUEUE_H
#define TINYLOG_FREELOCKQUEUE_H

#include <string>

class Node {
public:
    std::string data_;
    Node* next_;
};

class LockFreeQueue {
public:
    LockFreeQueue();

    ~LockFreeQueue();

    void Push(std::string &data);

    int32_t Pop(std::string &data);

private:
    Node* head_;
    Node* tail_;
};

#endif //TINYLOG_FREELOCKQUEUE_H
