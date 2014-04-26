//
//  Users.cpp
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Users.h"

map<unsigned int, User> Users::users;

User& Users::getFromUID(unsigned int uid)
{
    auto it = users.find(uid);
    if (it == users.end()) {
        throw string("User not found");
    }
    
    return it->second;
}

void Users::importFromFile(const string file)
{
    std::ifstream fin;
    fin.open(file);
    
    string line;
    
    users.clear();
    
    while (fin.good()) {
        std::getline(fin, line);
        try {
            auto u = User::fromString(line);
            users[u.getUID()] = u;
        } catch(...) {}
    }
    
    fin.close();
}

void Users::exportToFile(const string file)
{
    std::ofstream fout;
    fout.open(file);
    
    for (auto& pair : users) {
        fout << pair.second.toString() << std::endl;
    }
    
    fout.close();
}