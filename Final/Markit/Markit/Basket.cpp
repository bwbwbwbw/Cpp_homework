//
//  Basket.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Basket.h"

Basket& Basket::add(const BasketItem& item)
{
    for (auto& it : *this) {
        if (it.pid == item.pid) {
            it.quantity += item.quantity;
            return *this;
        }
    }
    
    push_back(item);
    return *this;
}

Basket& Basket::remove(unsigned int pid, unsigned int quantity)
{
    for (auto it = begin(); it != end(); ++it) {
        if (it->pid == pid) {
            if (it->quantity >= quantity) {
                it->quantity -= quantity;
            } else {
                it->quantity = 0;
                erase(it);
            }
            break;
        }
    }
    return *this;
}

unsigned int Basket::getTotalPrice100() const
{
    unsigned int ret = 0;
    
    for (auto& it : *this) {
        ret += ((int)it.price100 - (int)it.discount100) * it.quantity;
    }
    
    return ret;
}