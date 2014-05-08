//
//  BasketItem.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "BasketItem.h"

BasketItem::BasketItem(unsigned int _quantity, unsigned int _pid, unsigned int _discount100)
{
    Product& p = Products::getFromPID(_pid);
    BasketItem(_quantity, p, _discount100);
}

BasketItem::BasketItem(unsigned int _quantity, const Product& p, unsigned int _discount100)
{
    virt = false;
    
    pid = p.getPID();
    name = p.getName();
    price100 = p.getPrice100();
    discount100 = _discount100;
    quantity = _quantity;
}

BasketItem::BasketItem(unsigned int _quantity,
           unsigned int _pid,
           const string _name,
           unsigned int _price100,
           unsigned int _discount100
           )
{
    virt = true;
    
    pid = _pid;
    name = _name;
    price100 = _price100;
    discount100 = _discount100;
    quantity = _quantity;
}