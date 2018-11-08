//
//  main.cpp
//  cyk
//
//  Created by Luis Sandoval on 10/25/18.
//  Copyright © 2018 Luis Sandoval. All rights reserved.
//

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <iterator>
#include <array>

typedef enum
{
    S,
    R,
    D1,
    Cc,
    Cl
} N;

class set : public std::set<int>
{
  public:
    bool find(N x)
    {
        return !(std::set<int>::find(x) == end());
    }
};

typedef std::map<int, set> row;
typedef std::map<int, row> table;
typedef std::array<N, 2> production;
std::map<N, char> terminals;
std::map<N, production> variables;

int length(char *w)
{
    int i = 0;
    char *c = w;
    for (i = 0; c[i] != '\0'; i++);
    return i;
}

int main(int argc, const char *argv[])
{
    table t;
    char *s = new char[100];
    std::cout << "Enter string: ";
    std::cin >> s;
    int wLen = length(s);

    terminals.insert(std::pair<N, char>(S, 'x'));
    terminals.insert(std::pair<N, char>(R, 'r'));
    terminals.insert(std::pair<N, char>(Cl, 'l'));
    terminals.insert(std::pair<N, char>(Cc, 'c'));

    for(int i = 0; i < wLen; i++) {
        std::map<N, char>::iterator it = terminals.begin();
        while(it != terminals.end()) {
            if (it->second == s[i]) {
                t[i+1][1].insert(it->first);
            }
            it++;
        }
    }

    production prodS = {Cl, D1};    
    variables.insert(std::pair<N, production>(S, prodS));

    production prodR = {Cc, D1};    
    variables.insert(std::pair<N, production>(R, prodR));

    production prodD1 = {S, R};    
    variables.insert(std::pair<N, production>(D1, prodD1));

    for(int j = 2; j <= wLen; j++) {
        for(int i = 1; i <= (wLen-j+1); i++) {
            set G;
            for(int k = 1; k <= (j-1); k++) {
                std::map<N, production>::iterator it = variables.begin();
                while(it != variables.end()) {
                    if(t[i][k].find(it->second[0]) && t[i+k][j-k].find(it->second[1])) {
                        t[i][j].insert(it->first);
                    }
                    it++;
                }
            }
        }
    }

    if(t[1][wLen].find(S)) {
        std::cout << "Word is accepted by grammar" << std::endl;
    } else {
        std::cout << "Word is rejected by grammar" << std::endl;
    }

    return 0;
}
