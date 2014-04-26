//
//  main.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//
#include "Products.h"
#include "Users.h"
#include "Cards.h"
#include "UserLevels.h"
#include "UserLevelNormal.h"
#include "UserLevelSilver.h"
#include "UserLevelGold.h"

#include "FormUtils.h"
#include "FormWelcome.h"

int main()
{
    UserLevels::pushLevel(new UserLevelNormal());
    UserLevels::pushLevel(new UserLevelSilver());
    UserLevels::pushLevel(new UserLevelGold());
    
    Products::importFromFile("db_goods.csv");
    Users::importFromFile("db_users.csv");
    Cards::importFromFile("db_cards.csv");
    
    FormUtils::initialize();
    FormWelcome::show();
    FormUtils::finalize();
    
    return 0;
}