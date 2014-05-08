//
//  BasketItem.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__BasketItem__
#define __Markit__BasketItem__

#include <string>
#include "Product.h"
#include "Products.h"

using std::string;

class BasketItem
{
public:
    bool         virt;
    unsigned int pid;
    string       name;
    unsigned int price100;
    unsigned int discount100;
    unsigned int quantity;
    
    BasketItem(unsigned int _quantity, unsigned int _pid, unsigned int _discount100 = 0);
    BasketItem(unsigned int _quantity, const Product& p, unsigned int _discount100 = 0);
    BasketItem(unsigned int _quantity,
               unsigned int _pid,
               const string _name,
               unsigned int _price100,
               unsigned int _discount100 = 0
               );
};

#endif /* defined(__Markit__BasketItem__) */
