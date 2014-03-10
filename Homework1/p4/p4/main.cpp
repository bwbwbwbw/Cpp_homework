//
//  main.cpp
//  p4
//
//  Created by Breezewish on 14-2-26.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

typedef struct {
    std::string name;
    std::string mail;
    int id;
} student;

int main(int argc, const char * argv[])
{
    student me = {"Wenxuan Shi", "me@breeswish.org", 1352978};
    
    std::cout << std::left;
    std::cout << std::setw(7) << "Name:" << me.name << std::endl;
    std::cout << std::setw(7) << "Mail:" << me.mail << std::endl;
    std::cout << std::setw(7) << "ID:" << me.id << std::endl;
    
    student *that = &me;
    that->name = "Ye Sang";
    that->mail = "344***367@qq.com";
    that->id = 1351633;
    
    std::cout << std::endl;
    std::cout << std::setw(7) << "Name:" << that->name << std::endl;
    std::cout << std::setw(7) << "Mail:" << that->mail << std::endl;
    std::cout << std::setw(7) << "ID:" << that->id << std::endl;
    
    return 0;
}

