//
//  main.cpp
//  P1
//
//  Created by Breezewish on 5/8/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include <iostream>
#include "Stack.h"

int main(int argc, const char * argv[])
{
    Stack<int> s;
    
    try {
        s.push(1);
        s.push(2);
        s.pop();
        s.pop();
        s.pop();
        s.print();
    } catch (exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}

