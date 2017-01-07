//
// Created by ouyangliduo on 2017/1/7.
//

#include "LockFreeQueue.h"

#define CAS(ptr, old_value, new_value) __sync_bool_compare_and_swap(ptr, old_value, new_value)

LockFreeQueue::LockFreeQueue()
{
    Node* dumb = new Node();
    dumb->next_ = NULL;
    head_ = tail_ = dumb;
}

void LockFreeQueue::Push(std::string &data)
{
    Node* new_node= new Node;
    new_node->data_ = data;
    new_node->next_ = NULL;
    Node* tail;
    Node* next;

    while(true)
    {
        tail = tail_;
        next = tail->next_;

        if(tail != tail_) {
            continue;
        }

        if(next != NULL) {
            CAS(&tail_ , tail , next);
            continue;
        }

        if(CAS(&tail->next_ , next , new_node)) {
            break;
        }
    }

    CAS(&tail_ , tail , new_node);
}

int32_t LockFreeQueue::Pop(std::string &data)
{
    Node* head;
    Node* tail;
    Node* next;

    while(true)
    {
        head = head_;
        tail = tail_;
        next = head->next_;

        if(head != head_) {
            continue;
        }

        if(next == NULL) {
            return -1;
        }

        if(head == tail)
        {
            CAS(&tail_ , tail , next);
            continue;
        }
        data = next->data_;
        if(CAS(&head_ , head , next)) {
            break;
        }
    }

    delete head;
    return 0;
}
