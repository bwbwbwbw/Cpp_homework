//
//  UserLevels.cpp
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "UserLevels.h"

map<unsigned int, const UserLevel*> UserLevels::levels;

void UserLevels::pushLevel(const UserLevel* ul)
{
    levels[ul->getLID()] = ul;
}

const UserLevel* UserLevels::getAccesser(unsigned long point)
{
    for (auto& pair : levels) {
        if (point >= pair.second->getMinimumRequiredPoint1000()
            && point < pair.second->getMaximumRequiredPoint1000()
            ) {
            return pair.second;
        }
    }
    
    throw string("No available user level accesser");
}