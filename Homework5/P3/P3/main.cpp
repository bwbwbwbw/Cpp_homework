//
//  main.cpp
//  P3
//
//  Created by Breezewish on 14-3-28.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>

#include "Base.h"
#include "DerivedFoo.h"
#include "DerivedBar.h"

int main(int argc, const char * argv[])
{
    
    Base foo1 = DerivedFoo(1, 2);
    Base bar1 = DerivedBar(3, 4);
    
    std::cout << "foo1: " << foo1 << std::endl;
    std::cout << "bar1: " << bar1 << std::endl;
    
    Base foo2 = foo1.clone();
    Base bar2 = bar1.clone();
    
    std::cout << "foo2: " << foo2 << std::endl;
    std::cout << "bar2: " << bar2 << std::endl;
    
    foo1.setBaseMember(10);
    bar1.setBaseMember(20);
    
    std::cout << "foo1: " << foo1 << std::endl;
    std::cout << "bar1: " << bar1 << std::endl;
    std::cout << "foo2: " << foo2 << std::endl;
    std::cout << "bar2: " << bar2 << std::endl;
    
    return 0;
}

