//
//  Basket.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__Basket__
#define __Markit__Basket__

#include <vector>
#include "BasketItem.h"

using std::vector;

class Basket : public vector<BasketItem>
{
public:
    Basket& add(const BasketItem& item);
    Basket& remove(unsigned int pid, unsigned int quantity);
    
    unsigned int getTotalPrice100() const;
};

#endif /* defined(__Markit__Basket__) */
