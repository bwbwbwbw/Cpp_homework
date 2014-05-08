//
//  Stack.h
//  P1
//
//  Created by Breezewish on 5/8/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef P1_Stack_h
#define P1_Stack_h

#include <exception>
#include <string>
#include <iostream>

using namespace std;

class getting_from_empty : public exception
{
    virtual const char* what() const throw()
    {
        return "Trying to get elements from an empty stack";
    }
};

class filling_to_full : public exception
{
private:
    int _max;
public:
    filling_to_full(int max)
    {
        _max = max;
    }
    
    virtual const char* what() const throw()
    {
        string err;
        err = "Trying to fill elements to a full stack (max=" + to_string(_max) + ")";
        
        return err.c_str();
    }
};

template<typename T>
class Stack
{
private:
    T _data[20];
    int _size;
    
public:
    Stack()
    {
        _size = 0;
    }
    
    Stack& push(const T& e)
    {
        if (_size >= 20) {
            throw filling_to_full(20);
        }
        
        _data[_size++] = e;
        
        return *this;
    }
    
    T& pop()
    {
        if (_size <= 0) {
            throw getting_from_empty();
        }
        
        return _data[--_size];
    }
    
    T& peek() const
    {
        if (_size <= 0) {
            throw getting_from_empty();
        }
        
        return _data[_size - 1];
    }
    
    int size() const
    {
        return _size;
    }
    
    bool empty() const
    {
        return _size == 0;
    }
    
    void print() const
    {
        for (int i = 0; i < _size; ++i) {
            std::cout << _data[i] << " ";
        }
    }
};

#endif
