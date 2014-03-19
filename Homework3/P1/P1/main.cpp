//
//  main.cpp
//  P1
//
//  Created by Breezewish on 14-3-12.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
    using std::pair;
    
    std::map<string, bool> exWords;
    std::map<string, int> count;
    
    // read exclusive words
    std::ifstream fex;
    fex.open("exclude_words.txt");
    
    while (fex.good()) {
        string word;
        fex >> word;
        exWords[word] = true;
    }
    
    fex.close();
    
    // read article
    std::ifstream fin;
    fin.open("article.txt");
    
    while (fin.good()) {
        string word;
        fin >> word;
        
        word.erase(std::remove_if(word.begin(), word.end(), isNotLetter), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if (word.length() > 0 && exWords.find(word) == exWords.end()) {
            
            if (count.find(word) == count.end()) {
                count[word] = 1;
            } else {
                count[word]++;
            }
            
        }
    }
    
    fin.close();
    
    std::ofstream fout;
    
    // lexicographic order
    fout.open("3_1_1out.txt");
    
    for (auto &pair : count) {
        fout << std::left << std::setw(15) << pair.first << pair.second << std::endl;
    }
    
    fout.close();
    
    // frequency order
    fout.open("3_1_2out.txt");
    
    std::vector<pair<string, int>> v(count.begin(), count.end());
    std::sort(v.begin(), v.end(), [](const pair<string, int> &x, const pair<string, int> &y) -> bool
              {
                  return y.second < x.second;
              });
    
    for (auto &pair : v) {
        fout << std::left << std::setw(15) << pair.first << pair.second << std::endl;
    }
    
    fout.close();
    
    return 0;
}

