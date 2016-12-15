//
// Created by Administrator on 2016/12/15.
//

#ifndef TINYLOG_UTILS_H
#define TINYLOG_UTILS_H

#include <sys/time.h>
#include <string>

class Utils {
public:
    static void GetCurrentTime(std::string &ref_time);

    static void GetCurrentTime(struct timeval *tv, struct tm **tm);
};


#endif //TINYLOG_UTILS_H
