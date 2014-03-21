//
//  Matrix4.h
//  P2
//
//  Created by Breezewish on 14-3-21.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef __P2__Matrix4__
#define __P2__Matrix4__

#include <iomanip>
#include <iostream>

class Matrix4
{
public:
    Matrix4();
    Matrix4(float d[16]);
    Matrix4& add(const Matrix4 &m2);
    Matrix4& multiply(const Matrix4 &m2);
    void print() const;
    Matrix4& operator+=(const Matrix4 &m2);
    float& operator()(int row, int col);
    float operator()(int row, int col) const;
private:
    float data[4][4];
};

#endif /* defined(__P2__Matrix4__) */
