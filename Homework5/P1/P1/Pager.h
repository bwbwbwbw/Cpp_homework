//
//  Pager.h
//  P1
//
//  Created by Breezewish on 14-3-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef __P1__Pager__
#define __P1__Pager__

#include <string>

using std::string;

class Pager
{
protected:
    string _s;
public:
    Pager(string s):_s(s) {}
    Pager(const Pager &p):Pager(p._s) {}
    Pager& operator=(const Pager& p)
    {
        _s = p._s;
        return *this;
    }
};

#endif /* defined(__P1__Pager__) */
