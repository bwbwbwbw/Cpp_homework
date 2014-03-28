//
//  Timer.h
//  P2
//
//  Created by Breezewish on 14-3-27.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P2_Timer_h
#define P2_Timer_h

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

// From:
// http://abdullahakay.blogspot.com/2012/12/cross-platform-millisecond-timer.html

class Timer
{
private:
    
    /*
     获取当前毫秒级时间戳
     */
    int64_t getTimestampMS()
    {
#ifdef WIN32
        /* Windows */
        FILETIME ft;
        LARGE_INTEGER li;
        
        /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
         * to a LARGE_INTEGER structure. */
        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        
        uint64_t ret = li.QuadPart;
        ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
        ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */
        
        return ret;
#else
        /* Linux */
        struct timeval tv;
        
        gettimeofday(&tv, NULL);
        
        int64_t ret = tv.tv_usec;
        /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
        ret /= 1000;
        
        /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
        ret += (tv.tv_sec * 1000);
        
        return ret;
#endif
    }
    
    int64_t start;
    
public:
    Timer()
    {
        start = getTimestampMS();
    }
    
    /*
     计算从构造类开始流逝的时间（ms）
     */
    long elapsed()
    {
        return getTimestampMS() - start;
    }
};

#endif
