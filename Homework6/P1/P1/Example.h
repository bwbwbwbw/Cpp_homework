//
//  Example.h
//  P1
//
//  Created by Breezewish on 5/5/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef P1_Example_h
#define P1_Example_h

template<typename T>
class example
{
private:
    int m_iSize;
    T* m_pdArray;
    T m_dMin;
    T m_dMax;
public:
    example(T min, T max);
    example(const T* array, int size);
    T& operator[](int index);
    bool operator==(const example&) const;
    bool insert(const T*, int);
    bool insert(T);
    T min() const {  return m_dMin; }
    T max() const {  return m_dMax; }
    void min(T);
    void max(T);
    int count (T value) const;
};

#endif
