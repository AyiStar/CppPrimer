//
// Created by ayistar on 1/5/17.
//

// use a range for to
// change all the characters in a string to X

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s;
    cin >> s;
    for(auto &c: s){
        c = 'X';
    }
    cout << s << endl;
    return 0;
}
