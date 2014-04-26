//
//  Product.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Product.h"
#include "utils.h"

unsigned int Product::getPID() const
{
    return pid;
}

string Product::getName() const
{
    return name;
}

string Product::getFrom() const
{
    return from;
}

unsigned int Product::getPrice100() const
{
    return price100;
}

string Product::toString() const
{
    return std::to_string(pid)
            + "," + name
            + "," + from
            + "," + std::to_string(price100);
}

Product Product::fromString(const string csvLine)
{
    Product p;
    auto parts = Utils::split(csvLine, ',');
    
    if (parts.size() < 4) {
        throw string("Invalid csv input");
    }
    
    p.pid = std::stoi(parts[0]);
    
    p.name = parts[1];
    p.from = parts[2];
    p.price100 = std::stoi(parts[3]);
    
    return p;
}