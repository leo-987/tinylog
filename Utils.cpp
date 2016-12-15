//
// Created by Administrator on 2016/12/15.
//

#include "Utils.h"

void Utils::GetCurrentTime(std::string &ref_time)
{
    struct timeval tv;
    struct tm *pt_tm;

    gettimeofday(&tv, NULL);
    pt_tm = localtime(&tv.tv_sec);

    char buff[128];
    sprintf(buff, "%04d/%02d/%02d %2d:%2d:%2d.%3ld", 1900 + pt_tm->tm_year, pt_tm->tm_mon, pt_tm->tm_mday,
            pt_tm->tm_hour, pt_tm->tm_min, pt_tm->tm_sec, tv.tv_usec);

    ref_time = buff;
}

void Utils::GetCurrentTime(struct timeval *tv, struct tm **tm)
{
    gettimeofday(tv, NULL);
    *tm = localtime(&tv->tv_sec);
}