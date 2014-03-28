//
//  DerivedBar.h
//  P3
//
//  Created by Breezewish on 14-3-28.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P3_DerivedBar_h
#define P3_DerivedBar_h

#include "Base.h"
#include <iostream>

class DerivedBar : public Base
{
private:
    int derivedbar_member;
public:
    DerivedBar(int base_n, int derived_n):Base(base_n), derivedbar_member(derived_n) {}
    
    void setBarMember(int n)
    {
        derivedbar_member = n;
    }
    
    int getBarMember() const
    {
        return derivedbar_member;
    }
    
    virtual Base clone()
    {
        return DerivedBar(base_member, derivedbar_member);
    }
    
    friend std::ostream& operator<<(std::ostream &os, const DerivedBar &bar)
    {
        os << "base=" << bar.base_member << ", bar=" << bar.derivedbar_member;
        return os;
    }
};

#endif
