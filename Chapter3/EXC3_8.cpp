//
// Created by ayistar on 1/5/17.
//

// use while and for loops to
// change all the characters in a string to X

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    for(string::size_type i = 0; i < s1.size(); i++){
        s1[i] = 'X';
    }

    string::size_type j = 0;
    while(j < s2.size()){
        s2[j] = 'X';
        j++;
    }

    cout << s1 << endl;
    cout << s2 << endl;

    return 0;
}
