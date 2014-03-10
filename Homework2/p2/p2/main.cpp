//
//  main.cpp
//  p2
//
//  Created by Breezewish on 14-3-5.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include<iostream>
#include<vector>
#include<string>

template <class T> T max(const std::vector<T> &n);
template <class T> T max(T *n, int size);

int main(int argc, const char * argv[])
{
    std::vector<int> t1 = {1, 3, 5, 2, 9, 7, 8};
    std::cout << "T1: max=" << max(t1) << std::endl;
    
    std::vector<float> t2 = {1.1, 3.2, 5.3, 2.4, 9.5, 7.6, 8.7};
    std::cout << "T2: max=" << max(t2) << std::endl;
    
    std::vector<std::string> t3 = {"shi", "wen", "xuan", "sang", "ye"};
    std::cout << "T3: max=" << max(t3) << std::endl;
    
    int t4[] = {1, 3, 5, 2, 9, 7, 8};
    std::cout << "T4: max=" << max(t4, sizeof(t4) / sizeof(t4[0])) << std::endl;
    
    float t5[] = {1.1, 3.2, 5.3, 2.4, 9.5, 7.6, 8.7};
    std::cout << "T5: max=" << max(t5, sizeof(t5) / sizeof(t5[0])) << std::endl;
    
    std::string t6[] = {"shi", "wen", "xuan", "sang", "ye"};
    std::cout << "T6: max=" << max(t6, sizeof(t6) / sizeof(t6[0])) << std::endl;
    
    return 0;
}

// Func1
template <class T>
T max(const std::vector<T> &n)
{
    if (n.size() == 0) {
        return T();
    }
    
    auto max = n[0];
    
    for (auto it = ++n.begin(); it != n.end(); ++it) {
        if ((*it) > max) {
            max = *it;
        }
    }
    
    return max;
}

// Func2
template <class T>
T max(T *n, int size)
{
    if (size <= 0) {
        return T();
    }
    
    auto max = n[0];
    
    for (int i = 1; i < size; ++i) {
        if (n[i] > max) {
            max = n[i];
        }
    }
    
    return max;
}