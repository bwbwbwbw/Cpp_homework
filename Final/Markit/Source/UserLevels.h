//
//  UserLevels.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_UserLevels_h
#define Markit_UserLevels_h

#include <map>
#include "UserLevel.h"

using std::map;

class UserLevels
{
private:
    static map<unsigned int, const UserLevel*> levels;
public:
    static void pushLevel(const UserLevel* ul);
    static const UserLevel* getAccesser(unsigned long point);
};

#endif
