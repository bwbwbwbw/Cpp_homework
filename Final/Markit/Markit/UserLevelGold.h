//
//  UserLevelGold.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__UserLevelGold__
#define __Markit__UserLevelGold__

#include "UserLevel.h"

class UserLevelGold : public UserLevel
{
public:
    virtual string        getName() const
    {
        return "Gold User";
    }
    
    virtual unsigned int  getLID() const
    {
        return 2;
    }
    
    virtual unsigned long getMinimumRequiredPoint1000() const
    {
        return 50000L*1000;
    }
    
    virtual unsigned long getMaximumRequiredPoint1000() const
    {
        return (unsigned long)-1L;
    }
    
    virtual Basket        getDiscountBasket(const Basket& basket) const
    {
        Basket new_basket;
        
        for (auto& item : basket) {
            unsigned int price100 = item.price100;
            unsigned int discount100 = 0;
            
            if (price100 < 10*100) {
                discount100 = 0;
            } else if (price100 < 20*100) {
                discount100 = 0.05 * (float)price100;
            } else {
                discount100 = 0.1 * (float)price100;
            }
            
            new_basket.add(BasketItem(item.pid, discount100));
        }
        
        return new_basket;
    }
    
    virtual unsigned long getBonusPoint1000(const Basket& basket) const
    {
        unsigned int price100 = basket.getTotalPrice100();
        unsigned long bonus1000 = 0L;
        
        if (price100 < 1000*100) {
            bonus1000 += price100 * 15;
        } else {
            bonus1000 += 1000*100 * 15;
            if (price100 < 5000*100) {
                bonus1000 += (price100 - 1000*100) * 18;
            } else {
                bonus1000 += 4000*100 * 18;
                bonus1000 += (price100 - 5000*100) * 20;
            }
        }
        
        return bonus1000;
    }
};


#endif /* defined(__Markit__UserLevelGold__) */
