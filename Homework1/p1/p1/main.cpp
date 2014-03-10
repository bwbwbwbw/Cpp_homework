//
//  main.cpp
//  p1
//
//  Created by Breezewish on 14-2-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, const char * argv[])
{
    
    std::ifstream fin;
    fin.open("passage.txt");
    
    std::string word;
    int count = 0;
    
    while (fin.good()) {
        fin >> word;
        // TODO: cannot count words wrap with symbols.
        if (word == "that") {
            count++;
        }
    }
    
    fin.close();
    
    std::cout << "Count of \'that\': " << count << std::endl;
    
    return 0;
}

