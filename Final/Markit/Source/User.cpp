//
//  User.cpp
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "User.h"
#include "utils.h"

unsigned int User::getUID() const
{
    return uid;
}

string User::getName() const
{
    return name;
}

int User::getGender() const
{
    return gender;
}

string User::getTel() const
{
    return tel;
}

string User::getLevel() const
{
    return getAccesser()->getName();
}

unsigned long User::getPoint1000() const
{
    return point1000;
}

const UserLevel* User::getAccesser() const
{
    return UserLevels::getAccesser(point1000);
}

User& User::updatePoint1000(long addValue1000)
{
    point1000 += addValue1000;
    return *this;
}

string User::toString() const
{
    return std::to_string(uid)
            + "," + name
            + "," + std::to_string(gender)
            + "," + tel
            + "," + std::to_string(point1000);
}

User User::fromString(const string csvLine)
{
    User u;
    auto parts = Utils::split(csvLine, ',');
    
    if (parts.size() < 5) {
        throw string("Invalid csv input");
    }
    
    u.uid = std::stoi(parts[0]);
    u.name = parts[1];
    u.gender = std::stoi(parts[2]);
    u.tel = parts[3];
    u.point1000 = std::stoul(parts[4]);
    
    return u;
}