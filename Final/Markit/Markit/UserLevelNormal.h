//
//  UserLevelNormal.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__UserLevelNormal__
#define __Markit__UserLevelNormal__

#include "UserLevel.h"

class UserLevelNormal : public UserLevel
{
public:
    virtual string        getName() const
    {
        return "Normal User";
    }
    
    virtual unsigned int  getLID() const
    {
        return 0;
    }
    
    virtual unsigned long getMinimumRequiredPoint1000() const
    {
        return 0L;
    }
    
    virtual unsigned long getMaximumRequiredPoint1000() const
    {
        return 10000L * 1000;
    }
    
    virtual Basket        getDiscountBasket(const Basket& basket) const
    {
        return basket;
    }
    
    virtual unsigned long getBonusPoint1000(const Basket& basket) const
    {
        return 0L;
    }
};

#endif /* defined(__Markit__UserLevelNormal__) */
