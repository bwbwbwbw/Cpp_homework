//
//  Derived.h
//  P2
//
//  Created by Breezewish on 14-3-27.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P2_Derived_h
#define P2_Derived_h

class Derived : public Base
{
public:
    virtual void bar() {
        v++;
    }
};

#endif
