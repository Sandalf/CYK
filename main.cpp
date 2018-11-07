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
// std::map<N, std::string[2][2]> variables;
std::map<N, char> terminals;
typedef std::array<N, 2> combination;
typedef std::array<combination, 2> productions;
std::map<N, productions> variables;

void printGenerator(N i) {
    if (i == 0) {
        std::cout << "S" << " ";
    } else if (i == 1) {
        std::cout << "R" << " ";
    } else if (i == 2) {
        std::cout << "D1" << " ";
    } else if (i == 3) {
        std::cout << "D2" << " ";
    } else if (i == 4) {
        std::cout << "Cc" << " ";
    } else if (i == 5) {
        std::cout << "Cl" << " ";
    }
}

void print(set &a) {
    int items = 0;
    std::set<int>::iterator i = a.begin();
    while(i != a.end()) {
        if (*i == 0) {
            std::cout << "S " << " ";
        } else if (*i == 1) {
            std::cout << "R " << " ";
        } else if (*i == 2) {
            std::cout << "D1" << " ";
        } else if (*i == 3) {
            std::cout << "D2" << " ";
        } else if (*i == 4) {
            std::cout << "Cc" << " ";
        } else if (*i == 5) {
            std::cout << "Cl" << " ";
        }
        // std::cout << *i << " ";
        i++;
        items++;
    }

    if (items == 0) {
        std::cout << "   ";
    }
    // std::cout << std::endl;
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
            if (it->second == s[i]) {
                t[i+1][1].insert(it->first);
            }
            it++;
        }
    }

    std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    std::cout << "|"; print(t[1][1]); std::cout << "|" << "|"; print(t[0][2]); std::cout << "|" << "|"; print(t[0][3]); std::cout << "|" << std::endl;
    std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    std::cout << "+---+" << "+---+" << std::endl;
    std::cout << "|";  print(t[2][1]); std::cout <<  "|" << "|"; print(t[1][2]); std::cout <<"|" << std::endl;
    std::cout << "+---+" << "+---+" << std::endl;
    std::cout << "+---+" << std::endl;
    std::cout << "|";  print(t[3][1]); std::cout << "|" << std::endl;
    std::cout << "+---+" << std::endl;

    // return 0;

    combination comD1 = {S, R};
    productions prodD1 = {comD1};
    variables.insert(std::pair<N, productions>(R, prodD1));

    combination comS = {Cl, D1};
    productions prodS = {comS};
    variables.insert(std::pair<N, productions>(S, prodS));

    combination comR = {Cc, D1};
    productions prodR = {comR};
    variables.insert(std::pair<N, productions>(R, prodR));

    for(int j = 2; j <= 3; j++) {
        std::cout << "j: " << j << std::endl;
        for(int i = 1; i <= (3-j+1); i++) {
            std::cout << "i: " << i << std::endl;
            set G;
            for(int k = 1; k <= (j-1); k++) {
                std::cout << "k: " << k << std::endl;
                std::map<N, productions>::iterator it = variables.begin();
                while(it != variables.end()) {
                    std::cout << "t[i][k]: " << "t[" << i << "][" << k << "]" << std::endl;
                    std::cout << "t[i+k][j-k]: " << "t[" << (i+k) << "][" << (j-k) << "]" << std::endl;
                    // print(t[k][i]);
                    // print(t[i+k][j-k]);
                    if(t[i][k].find(it->second[0][0]) && t[i+k][j-k].find(it->second[0][1])) {
                        std::cout << "Found match: ";
                        printGenerator(it->second[0][0]);
                        std::cout << ", ";
                        printGenerator(it->second[0][1]);
                        std::cout << std::endl;
                        t[i][j].insert(it->first);
                    } else {
                        // printGenerator(it->second[0][0]);
                        std::cout << "No match found: ";
                        printGenerator(it->second[0][0]);
                        std::cout << ", ";
                        printGenerator(it->second[0][1]);
                        std::cout << std::endl;
                    }
                    std::cout  << std::endl;
                    it++;
                }
                    // std::set<int>::iterator it = t[i][k].begin();
                    // while(it != t[i][k].end()) {
                    //     std::set<int>::iterator it2 = t[i][k].begin();
                    //     while(it2 != t[i][k].end()) {
                    //         // std::cout << *it2 << " ";
                    //         std::map<N, productions>::iterator it3 = variables.begin();
                    //         while(it3 != variables.end()) {
                    //             for(int l = 0; l < 2; l++) {
                    //                 combination comb = {it, it2};
                    //                 if (it == it3->second[0]) {

                    //                 }
                    //                 it3->second[l];
                    //             }
                    //             it3++;
                    //         }

                    //         it2++;
                    //     }
                    //     it++;
                    // }
                    // combination comb  = 
                    // t[i][k] = t[i+k][j-k];
            }
        }
    }

    std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    std::cout << "|"; print(t[0][0]); std::cout << "|" << "|"; print(t[0][1]); std::cout << "|" << "|"; print(t[0][2]); std::cout << "|" << std::endl;
    std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    std::cout << "+---+" << "+---+" << std::endl;
    std::cout << "|";  print(t[1][0]); std::cout <<  "|" << "|"; print(t[1][1]); std::cout <<"|" << std::endl;
    std::cout << "+---+" << "+---+" << std::endl;
    std::cout << "+---+" << std::endl;
    std::cout << "|";  print(t[2][0]); std::cout << "|" << std::endl;
    std::cout << "+---+" << std::endl;

    // print(t[0][1]);
    // print(t[1][1]);
    // print(t[2][1]);

    // print(t[0][2]);
    // print(t[1][2]);

    // print(t[0][3]);
    // print(t[1][3]);

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
