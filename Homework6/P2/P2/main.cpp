//
//  main.cpp
//  P2
//
//  Created by Breezewish on 5/5/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"

int main(int argc, const char * argv[])
{
    Matrix<float> m1(2, 2);
    
    m1(0, 0) = 0.0;
    m1(0, 1) = 1.0;
    m1(1, 0) = 2.0;
    m1(1, 1) = 3.0;
    
    float data[] = {1.0, 0.0, 0.0, 1.0};
    Matrix<float> m2(2, 2, data);
    
    m2.print();std::cout << std::endl;
    m1.multiply(m2).print();std::cout << std::endl;
    m1.add(m2).print();
    
    return 0;
}

