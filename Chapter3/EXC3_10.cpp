//
// Created by ayistar on 1/6/17.
//

// read a string of characters including punctuation 
// and write what was read but with the punctuation removed

#include <iostream>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s;
    cin >> s;
    
    for(auto c: s){
        if(!ispunct(c)){
            cout << c;
        }
    }
    cout << endl;
    
    return 0;
}