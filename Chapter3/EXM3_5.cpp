//
// Created by ayistar on 1/5/17.
//

// convert the whole string to uppercase

#include <iostream>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s("Hello World!!!");
    for(auto &c: s){
        c = toupper(c);
    }
    cout << s << endl;
    return 0;
}
