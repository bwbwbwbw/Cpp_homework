//
//  UserLevel.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__UserLevel__
#define __Markit__UserLevel__

#include "Basket.h"

class UserLevel
{
public:
    virtual string        getName()                                  const = 0;
    virtual unsigned int  getLID()                                   const = 0;
    virtual unsigned long getMinimumRequiredPoint1000()              const = 0;
    virtual unsigned long getMaximumRequiredPoint1000()              const = 0;
    virtual Basket        getDiscountBasket(const Basket& basket)    const = 0;
    virtual unsigned long getBonusPoint1000(const Basket& basket)    const = 0;
};

#endif /* defined(__Markit__UserLevel__) */
