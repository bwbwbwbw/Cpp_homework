//
//  BusinessTraveler.h
//  P1
//
//  Created by Breezewish on 14-3-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef __P1__BusinessTraveler__
#define __P1__BusinessTraveler__

#include <string>

#include "Traveler.h"
#include "Pager.h"

using std::string;

class BusinessTraveler : public Traveler
{
private:
    Pager _p;
public:
    BusinessTraveler():Traveler(""),_p("") {}
    BusinessTraveler(const string &s):Traveler(s),_p(s) {}
    BusinessTraveler(const BusinessTraveler &bt):Traveler(bt._s), _p(bt._p) {}
    BusinessTraveler& operator=(const BusinessTraveler &bt)
    {
        _s = bt._s;
        _p = bt._p;
        return *this;
    }
};

#endif /* defined(__P1__BusinessTraveler__) */
