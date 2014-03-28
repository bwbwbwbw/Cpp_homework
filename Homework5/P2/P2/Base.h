//
//  Base.h
//  P2
//
//  Created by Breezewish on 14-3-27.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef P2_Base_h
#define P2_Base_h

class Base
{
protected:
    unsigned int v;
public:
    Base():v(0) {}
    void foo() {
        v++;
    }
    virtual void bar() {}
};

#endif
