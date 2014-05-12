//
//  FormSave.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormSave_h
#define Markit_FormSave_h

#include "FormUtils.h"
#include "Users.h"
#include "Cards.h"

class FormSave
{
public:
    static void show()
    {
        newtWinMessage((char*)"Markit", (char*)"OK", (char*)"Database saved successfully.");
    }
    
    static void execute()
    {
        Users::exportToFile("db_users.csv");
        Cards::exportToFile("db_cards.csv");
        show();
    }
};

#endif
