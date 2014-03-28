//
//  main.cpp
//  P2
//
//  Created by Breezewish on 14-3-27.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>

#include "Base.h"
#include "Derived.h"
#include "Timer.h"

const int LOOP_TIMES = 1e9;

int main(int argc, const char * argv[])
{
    Base obj = Derived();
    
    Timer t1;
    for (int i = 0; i < LOOP_TIMES; ++i) {
        obj.foo();
    }
    std::cout << "          foo: " << t1.elapsed() << "ms" << std::endl;
    
    Timer t2;
    for (int i = 0; i < LOOP_TIMES; ++i) {
        obj.bar();
    }
    std::cout << "(virtual) bar: " << t2.elapsed() << "ms" << std::endl;
    
    return 0;
}

