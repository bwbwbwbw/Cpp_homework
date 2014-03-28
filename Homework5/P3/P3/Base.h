//
//  Base.h
//  P3
//
//  Created by Breezewish on 14-3-28.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P3_Base_h
#define P3_Base_h

class Base
{
protected:
    int base_member;
public:
    Base(int n):base_member(n){}
    
    void setBaseMember(int n)
    {
        base_member = n;
    }
    
    int getBaseMember() const
    {
        return base_member;
    }
    
    virtual Base clone()
    {
        return Base(base_member);
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Base &base)
    {
        os << "base=" << base.base_member;
        return os;
    }
};

#endif
