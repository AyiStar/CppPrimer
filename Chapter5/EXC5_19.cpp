//
// Created by ayistar on 1/12/17.
//

// use a do while loop
// to repetitively request two strings from the user
// and report which string is smaller

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1, s2;
    string s;

    do {
        cout << "Input two strings: " << endl;
        cin >> s1 >> s2;
        cout << "s" << ((s1 < s2) ? '1' : '2') << " is smaller" << endl;
        cout << endl << "Another two strings? (yes or no)" << endl;
        cin >> s;
    } while (!s.empty() && s[0] == 'y');
    
    return 0;
}

