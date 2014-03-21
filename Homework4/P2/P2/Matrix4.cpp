//
//  Matrix4.cpp
//  P2
//
//  Created by Breezewish on 14-3-21.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include "Matrix4.h"

Matrix4::Matrix4()
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            std::cin >> data[row][col];
        }
    }
}

Matrix4::Matrix4(float d[16])
{
    int ps = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            data[row][col] = d[ps++];
        }
    }
}

Matrix4& Matrix4::add(const Matrix4 &m2)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            data[row][col] += m2.data[row][col];
        }
    }
    
    return *this;
}

Matrix4& Matrix4::multiply(const Matrix4 &m2)
{
    int val[4][4];
    
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            val[row][col] = 0.0;
            for (int n = 0; n < 4; ++n) {
                val[row][col] += data[row][n] * m2.data[n][col];
            }
        }
    }
    
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            data[row][col] = val[row][col];
        }
    }
    
    return *this;
}

void Matrix4::print() const
{
    std::cout << std::left;
    
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            std::cout << std::setw(10) << data[row][col];
        }
        std::cout << std::endl;
    }
}

Matrix4& Matrix4::operator+=(const Matrix4 &m2)
{
    return add(m2);
}

float& Matrix4::operator()(int row, int col)
{
    return data[row][col];
}

float Matrix4::operator()(int row, int col) const
{
    return data[row][col];
}
