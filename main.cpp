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
#include <algorithm>
#include <array>

typedef enum
{
    S,
    R,
    D1,
    D2,
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
std::map<N, std::string[2][2]> variables;
std::map<N, char> terminals;
typedef std::array<N, 2> combination;
typedef std::array<combination, 2> productions;
std::map<N, productions> mymap;

void print(set &a) {
    std::set<int>::iterator i = a.begin();
    while(i != a.end()) {
        std::cout << *i << " ";
        i++;
    }
    std::cout << std::endl;
}

int main(int argc, const char *argv[])
{
    table t;
    char* s = (char*)"lxr";

    terminals.insert(std::pair<N, char>(S, 'x'));
    terminals.insert(std::pair<N, char>(R, 'r'));
    terminals.insert(std::pair<N, char>(Cl, 'l'));
    terminals.insert(std::pair<N, char>(Cc, 'c'));

    for(int i = 0; i < 3; i++) {
        std::map<N, char>::iterator it = terminals.begin();
        while(it != terminals.end()) {
            // std::cout << it->first << ": " << it->second << " ";
            if (it->second == s[i]) {
                // std::cout << it->second << " & " << s[i] << " are equal";
                t[i][1].insert(it->first);
            }
            it++;
        }
        // std::cout << std::endl;
    }

    print(t[0][1]);
    print(t[1][1]);
    print(t[2][1]);

    // combination comb = {Cl, D1};
    // productions sProductions = {comb,comb};
    // mymap.insert(std::pair<N, productions> (S, sProductions));

    // S -> x | ClD1
    // variables.insert(std::pair<N, std::string[]>(S,{"",""}));
    // variables[S] = new std::string[2];
    // variables[S][0] = "x";
    // variables[S][1] = "Cl D1";

    // R -> r | CcD1
    // variables[R][0] = "r";
    // variables[R][1] = "Cc D1";

    // Cc -> c
    // terminals[Cc][0] = 'c';

    // D1 -> SR
    // variables[D1][0] = "S R";

    // Cl -> l
    // terminals[Cl][0] = 'l';

    return 0;
}
