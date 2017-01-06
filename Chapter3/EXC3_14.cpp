//
// Created by ayistar on 1/6/17.
//

// read a sequence of ints from cin and store those values in a vector
// repeat it but read strings instead.

#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<int> ivec;
    vector<string> svec;
    int ival;
    string str;
    
    while(cin >> ival){
        ivec.push_back(ival);
    }
    while(cin >> str){
        svec.push_back(str);
    }
    
    return 0;
}