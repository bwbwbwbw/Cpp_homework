//
//  main.cpp
//  P2
//
//  Created by Breezewish on 14-3-18.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool isNotLetter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return false;
    } else {
        return true;
    }
}

int main(int argc, const char * argv[])
{
    using std::string;
    
    std::vector<string> v;
    
    // read
    std::ifstream fin;
    fin.open("article.txt");
    
    while (fin.good()) {
        string word;
        fin >> word;
        
        word.erase(std::remove_if(word.begin(), word.end(), isNotLetter), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if (word.length() > 0) {
            v.push_back(word);
        }
    }
    
    fin.close();
    
    // sort
    std::sort(v.begin(), v.end(), [](string &a, string &b) -> bool
              {
                  return a.length() < b.length();
              });
    
    // print
    std::ofstream fout;
    fout.open("3_2out.txt");
    
    for (auto &s : v) {
        fout << s << " ";
    }
    fout << std::endl;
    
    fout.close();
    
    return 0;
}

