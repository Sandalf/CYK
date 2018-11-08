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
typedef std::array<N, 2> combination;
typedef std::array<combination, 2> productions;
std::map<N, char> terminals;
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

        i++;
        items++;
    }

    if (items == 0) {
        std::cout << "   ";
    }
}

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
    // char* s = (char*)"lxr\0"; // accepted
    // char* s = (char*)"lxcxr\0"; // accepted
    char* s = (char*)"lxr\0"; // accepted
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

    // std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    // std::cout << "|"; print(t[1][1]); std::cout << "|" << "|"; print(t[0][2]); std::cout << "|" << "|"; print(t[0][3]); std::cout << "|" << std::endl;
    // std::cout << "+---+" << "+---+" << "+---+" << std::endl;
    // std::cout << "+---+" << "+---+" << std::endl;
    // std::cout << "|";  print(t[2][1]); std::cout <<  "|" << "|"; print(t[1][2]); std::cout <<"|" << std::endl;
    // std::cout << "+---+" << "+---+" << std::endl;
    // std::cout << "+---+" << std::endl;
    // std::cout << "|";  print(t[3][1]); std::cout << "|" << std::endl;
    // std::cout << "+---+" << std::endl;

    combination comS = {Cl, D1};
    productions prodS = {comS};
    variables.insert(std::pair<N, productions>(S, prodS));

    combination comR = {Cc, D1};
    productions prodR = {comR};
    variables.insert(std::pair<N, productions>(R, prodR));

    combination comD1 = {S, R};
    productions prodD1 = {comD1};
    variables.insert(std::pair<N, productions>(D1, prodD1));

    for(int j = 2; j <= wLen; j++) {
        // std::cout << "j: " << j << std::endl;
        for(int i = 1; i <= (wLen-j+1); i++) {
            // std::cout << "i: " << i << std::endl;
            set G;
            for(int k = 1; k <= (j-1); k++) {
                // std::cout << "k: " << k << std::endl;
                std::map<N, productions>::iterator it = variables.begin();
                while(it != variables.end()) {
                    // std::cout << "Generator: ";
                    // printGenerator(it->first);
                    // std::cout << std::endl;

                    // std::cout << "t[i][k]: " << "t[" << i << "][" << k << "]" << std::endl;
                    // std::cout << "t[i+k][j-k]: " << "t[" << (i+k) << "][" << (j-k) << "]" << std::endl;

                    if(t[i][k].find(it->second[0][0]) && t[i+k][j-k].find(it->second[0][1])) {
                        // std::cout << "Found match: ";
                        // printGenerator(it->second[0][0]);
                        // std::cout << ", ";
                        // printGenerator(it->second[0][1]);
                        // std::cout << std::endl;
                        t[i][j].insert(it->first);
                        // std::cout << "Inserted "; 
                        // printGenerator(it->first);
                        // std::cout << "in [i][j]: " << "t[" << i << "][" << j << "]" << std::endl;
                        // print(t[i][j]);
                    } else {
                        // std::cout << "No match found: ";
                        // printGenerator(it->second[0][0]);
                        // std::cout << ", ";
                        // printGenerator(it->second[0][1]);
                        // std::cout << std::endl;
                    }
                    // std::cout  << std::endl;
                    it++;
                }
            }
        }
    }
    
    // std::cout << "     1  " << "  2  " << "  3  " << std::endl;
    // std::cout << "   +---+" << "+---+" << "+---+" << std::endl;
    // std::cout << " 1 |"; print(t[1][1]); std::cout << "|" << "|"; print(t[1][2]); std::cout << "|" << "|"; print(t[1][3]); std::cout << "|" << std::endl;
    // std::cout << "   +---+" << "+---+" << "+---+" << std::endl;
    // std::cout << "   +---+" << "+---+" << std::endl;
    // std::cout << " 2 |";  print(t[2][1]); std::cout <<  "|" << "|"; print(t[2][2]); std::cout <<"|" << std::endl;
    // std::cout << "   +---+" << "+---+" << std::endl;
    // std::cout << "   +---+" << std::endl;
    // std::cout << " 3 |";  print(t[3][1]); std::cout << "|" << std::endl;
    // std::cout << "   +---+" << std::endl;

    if(t[1][wLen].find(S)) {
        std::cout << "Word is accepted by grammar" << std::endl;
    } else {
        std::cout << "Word is not accepted by grammar" << std::endl;
    }

    return 0;
}
