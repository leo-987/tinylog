//
// Created by ouyangliduo on 2016/12/13.
//

#include "TinyLog.h"

void *ThreadFunc(void *arg)
{

}

TinyLog::TinyLog()
{
    pt_logstream_ = new LogStream();
}

TinyLog::~TinyLog()
{

}

