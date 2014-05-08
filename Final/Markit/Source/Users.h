//
//  Users.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_Users_h
#define Markit_Users_h

#include <fstream>
#include <string>
#include <map>
#include "User.h"

using std::map;

class Users
{
private:
    static map<unsigned int, User> users;
public:
    static User& getFromUID(unsigned int uid);
    static void importFromFile(const string file);
    static void exportToFile(const string file);
};

#endif
