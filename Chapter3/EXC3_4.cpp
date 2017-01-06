//
// Created by ayistar on 1/5/17.
//

// read two strings and report whether the strings are equal.
// if not, report which of the two is larger.
// and then report whether the strings have the same lengrh.
// if not, report which is longer.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    if(s1 == s2){
        cout << "The two strings are equal" << endl;
    }
    else if(s1 < s2){
            cout << "s2 is the larger one" << endl;
        }
    else {
        cout << "s1 is the larger one" << endl;
    }


    if(s1.size() == s2.size()){
        cout << "The two strings have the same length" << endl;
    }
    else if(s1.size() < s2.size()){
        cout << "s2 is longer" << endl;
    }
    else{
        cout << "s1 is longer" << endl;
    }

    return 0;
}
