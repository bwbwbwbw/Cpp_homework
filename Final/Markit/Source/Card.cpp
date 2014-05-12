//
//  Card.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Card.h"
#include "Utils.h"

string Card::getCID() const
{
    return cid;
}

unsigned int Card::getBalance100() const
{
    return balance100;
}

Card& Card::updateBalance100(int addValue100)
{
    if ((int)balance100 + addValue100 < 0) {
        throw string("Insufficient Gift Card balance");
    }
    
    balance100 += addValue100;
    
    return *this;
}

string Card::toString() const
{
    return cid
        + "," + std::to_string(balance100);
}

Card Card::fromString(const string csvLine)
{
    Card c;
    auto parts = Utils::split(csvLine, ',');
    
    if (parts.size() < 2) {
        throw string("Invalid csv input");
    }
    
    c.cid = parts[0];
    c.balance100 = std::stoi(parts[1]);
    
    return c;
}