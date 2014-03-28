//
//  DerivedFoo.h
//  P3
//
//  Created by Breezewish on 14-3-28.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P3_DerivedFoo_h
#define P3_DerivedFoo_h

#include "Base.h"

class DerivedFoo : public Base
{
private:
    int derivedfoo_member;
public:
    DerivedFoo(int base_n, int derived_n):Base(base_n), derivedfoo_member(derived_n) {}
    
    void setFooMember(int n)
    {
        derivedfoo_member = n;
    }
    
    int getFooMember() const
    {
        return derivedfoo_member;
    }
    
    virtual Base clone()
    {
        return DerivedFoo(base_member, derivedfoo_member);
    }
    
    friend std::ostream& operator<<(std::ostream &os, const DerivedFoo &foo)
    {
        os << "base=" << foo.base_member << ", foo=" << foo.derivedfoo_member;
        return os;
    }
};

#endif
