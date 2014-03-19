//
//  main.cpp
//  P3
//
//  Created by Breezewish on 14-3-18.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

int main(int argc, const char * argv[])
{
    std::vector<int> v;
    
    std::copy(
              std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(v)
              );
    
    std::vector<int> oddNumbers, evenNumbers;
    oddNumbers.reserve(v.size());
    evenNumbers.reserve(v.size());
    
    for (auto n : v) {
        if ((n & 1) == 1) {
            oddNumbers.push_back(n);
        } else {
            evenNumbers.push_back(n);
        }
    }
    
    std::ofstream foutOdd;
    foutOdd.open("3_3_1out.txt");
    std::ostream_iterator<int> os1(foutOdd, " ");
    std::copy(oddNumbers.begin(), oddNumbers.end(), os1);
    foutOdd.close();
    
    std::ofstream foutEven;
    foutEven.open("3_3_2out.txt");
    std::ostream_iterator<int> os2(foutEven, "\n");
    std::copy(evenNumbers.begin(), evenNumbers.end(), os2);
    foutEven.close();
    
    return 0;
}

