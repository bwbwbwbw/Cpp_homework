//
//  main.cpp
//  p3
//
//  Created by Breezewish on 14-2-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <string>

void foo(std::string &str)
{
    str = "hello";
}

void bar(std::string *str)
{
    *str = std::string("world");
}

int main(int argc, const char * argv[])
{
    std::string s = "yoooooo";
    
    std::cout << "original:  " << s << std::endl;
    foo(s);
    std::cout << "modify(1): " << s << std::endl;
    bar(&s);
    std::cout << "modify(2): " << s << std::endl;
    
    return 0;
}

