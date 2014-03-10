//
//  main.cpp
//  p2
//
//  Created by Breezewish on 14-2-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iomanip>

float f()
{
    static float a = 0.1, b = 0.1;
    float c = a + b;
    a = b;
    b = c;
    return c;
}

void print(std::vector<float> v)
{
    std::cout << std::left;
    std::cout << std::setw(7) << "index" << "value" << std::endl;
    for (int i = 0, len = (int)v.size(); i < len; ++i) {
        std::cout << std::setw(7) << i << v[i] << std::endl;
    }
}

int main(int argc, const char * argv[])
{
    std::vector<float> v;
    v.reserve(25); // for performance
    
    for (int i = 0; i < 25; ++i) {
        v.push_back(f());
    }
    
    std::cout << "Before: " << std::endl;
    print(v);
    
    for (int i = 0, len = (int)v.size(); i < len; ++i) {
        v[i] = v[i] * v[i];
    }
    
    std::cout << std::endl;
    std::cout << "After: " << std::endl;
    print(v);
    
    return 0;
}

