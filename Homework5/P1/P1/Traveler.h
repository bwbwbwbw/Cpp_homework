//
//  Traveler.h
//  P1
//
//  Created by Breezewish on 14-3-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef __P1__Traveler__
#define __P1__Traveler__

#include <string>

using std::string;

class Traveler
{
protected:
    string _s;
public:
    Traveler(string s):_s(s) {}
    Traveler(const Traveler &t):Traveler(t._s) {}
    Traveler& operator=(const Traveler& t)
    {
        _s = t._s;
        return *this;
    }
};

#endif /* defined(__P1__Traveler__) */
