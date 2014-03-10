//
//  main.cpp
//  p1
//
//  Created by Breezewish on 14-3-5.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include<iostream>
#include<vector>
#include<string>

int max(const std::vector<int> &n);
float max(const std::vector<float> &n);
std::string max(const std::vector<std::string> &n);
int max(int *n, int size);
float max(float *n, int size);
std::string max(std::string *n, int size);

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
int max(const std::vector<int> &n)
{
    if (n.size() == 0) {
        return -1;
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
float max(const std::vector<float> &n)
{
    if (n.size() == 0) {
        return -1;
    }
    
    auto max = n[0];
    
    for (auto it = ++n.begin(); it != n.end(); ++it) {
        if ((*it) > max) {
            max = *it;
        }
    }
    
    return max;
}

// Func3
std::string max(const std::vector<std::string> &n)
{
    if (n.size() == 0) {
        return std::string();
    }
    
    auto max = n[0];
    
    for (auto it = ++n.begin(); it != n.end(); ++it) {
        if ((*it) > max) {
            max = *it;
        }
    }
    
    return max;
}

// Func4
int max(int *n, int size)
{
    if (size <= 0) {
        return -1;
    }
    
    auto max = n[0];
    
    for (int i = 1; i < size; ++i) {
        if (n[i] > max) {
            max = n[i];
        }
    }
    
    return max;
}

// Func5
float max(float *n, int size)
{
    if (size <= 0) {
        return -1;
    }
    
    auto max = n[0];
    
    for (int i = 1; i < size; ++i) {
        if (n[i] > max) {
            max = n[i];
        }
    }
    
    return max;
}

// Func6
std::string max(std::string *n, int size)
{
    if (size <= 0) {
        return std::string();
    }
    
    auto max = n[0];
    
    for (int i = 1; i < size; ++i) {
        if (n[i] > max) {
            max = n[i];
        }
    }
    
    return max;
}