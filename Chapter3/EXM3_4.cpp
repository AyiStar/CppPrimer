//
// Created by ayistar on 1/5/17.
//

// use a range for and the ispunct function
// to count the number of punctuation characters in a string

#include <iostream>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s("Hello World!!!");
    decltype(s.size()) punct_cnt = 0;
    for(auto c: s){
        if(ispunct(c)){
            ++punct_cnt;
        }
    }
    cout << punct_cnt << " punctuation characters in "
                      << s << endl;

    return 0;
}