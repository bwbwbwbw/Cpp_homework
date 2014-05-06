//
//  Matrix.h
//  P2
//
//  Created by Breezewish on 5/5/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __P2__Matrix__
#define __P2__Matrix__

#include <iostream>
#include <iomanip>

template<typename T>
class Matrix
{
private:
    int _rows;
    int _cols;
    T* _data;
public:
    Matrix(int rows, int cols)
    {
        _rows = rows;
        _cols = cols;
        _data = new T(_rows * _cols);
    }
    
    Matrix(int rows, int cols, const T* value) : Matrix(rows, cols)
    {
        for (int i = 0, end = _rows * _cols; i < end; ++i) {
            _data[i] = value[i];
        }
    }
    
    ~Matrix()
    {
        delete[] _data;
    }
    
    Matrix(const Matrix& m2) : Matrix(m2._rows, m2._cols, m2._data)
    {
    }
    
    Matrix& operator=(const Matrix& m2)
    {
        delete[] _data;
        
        _rows = m2._rows;
        _cols = m2._cols;
        _data = new T(_rows * _cols);
        
        for (int i = 0, end = _rows * _cols; i < end; ++i) {
            _data[i] = m2._data[i];
        }
        
        return *this;
    }
    
    Matrix add(const Matrix& m2)
    {
        if (m2._rows != _rows || m2._cols != _cols) {
            throw "Size error";
        }
        
        Matrix<T> _new(_rows, _cols, _data);
        
        for (int i = 0, end = _rows * _cols; i < end; ++i) {
            _new._data[i] += m2._data[i];
        }
        
        return _new;
    }
    
    Matrix multiply(const Matrix& m2)
    {
        if (_cols != m2._rows) {
            throw "Size error";
        }
        
        Matrix<T> _new(_rows, m2._cols);
        
        for (int row = 0; row < _rows; ++row) {
            for (int col = 0; col < m2._cols; ++col) {
                T r = 0;
                for (int n = 0; n < _cols; ++n) {
                    r += get(row, n) * m2.get(n, col);
                }
                
                _new.set(row, col, r);
            }
        }
        
        return _new;
    }
    
    void print() const
    {
        std::cout << std::left;
        
        std::cout.precision(2);
        
        for (int row = 0; row < _rows; ++row) {
            for (int col = 0; col < _cols; ++col) {
                std::cout << std::setw(10) << get(row, col);
            }
            std::cout << std::endl;
        }
    }
    
    T get(int row, int col) const
    {
        return _data[row * _cols + col];
    }
    void set(int row, int col, const T& value)
    {
        _data[row * _cols + col] = value;
    }
    T& operator()(int row, int col)
    {
        return _data[row * _cols + col];
    }
    T operator()(int row, int col) const
    {
        return _data[row * _cols + col];
    }
};

#endif /* defined(__P2__Matrix__) */
