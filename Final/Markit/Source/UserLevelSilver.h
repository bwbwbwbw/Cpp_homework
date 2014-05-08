//
//  UserLevelSilver.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__UserLevelSilver__
#define __Markit__UserLevelSilver__

#include "UserLevel.h"

class UserLevelSilver : public UserLevel
{
public:
    virtual string        getName() const
    {
        return "Silver User";
    }
    
    virtual unsigned int  getLID() const
    {
        return 1;
    }
    
    virtual unsigned long getMinimumRequiredPoint1000() const
    {
        return 10000L*1000;
    }
    
    virtual unsigned long getMaximumRequiredPoint1000() const
    {
        return 50000L * 1000;
    }
    
    virtual Basket        getDiscountBasket(const Basket& basket) const
    {
        Basket new_basket = basket;
        
        unsigned int price100 = basket.getTotalPrice100();
        unsigned int discount100 = 0;
        
        if (price100 < 1000*100) {
            discount100 += (float)price100 * 0.05;
        } else {
            discount100 += (float)1000*100 * 0.05;
            if (price100 < 2000*100) {
                discount100 += (float)(price100 - 1000*100) * 0.1;
            } else {
                discount100 += (float)1000*100 * 0.1;
                discount100 += (float)(price100 - 2000*100) * 0.15;
            }
        }
        
        new_basket.add(BasketItem(1, 0, "Discount", 0, discount100));
        
        return new_basket;
    }
    
    virtual unsigned long getBonusPoint1000(const Basket& basket) const
    {
        unsigned int price100 = basket.getTotalPrice100();
        unsigned long bonus1000 = 0L;
        
        if (price100 < 2000*100) {
            bonus1000 += price100 * 12;
        } else {
            bonus1000 += 2000*100 * 12;
            if (price100 < 5000*100) {
                bonus1000 += (price100 - 2000*100) * 15;
            } else {
                bonus1000 += 3000*100 * 15;
                bonus1000 += (price100 - 5000*100) * 18;
            }
        }
        
        return bonus1000;
    }
};

#endif /* defined(__Markit__UserLevelSilver__) */
