//
// Created by ayistar on 1/5/17.
//

// read an unknown number of strings

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string word;
    while(cin >> word){
        // read until eof
        cout << word << endl;
    }
    return 0;
}

