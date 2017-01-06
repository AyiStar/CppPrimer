//
// Created by ayistar on 1/5/17.
//

// read input a line at a time
// and discard blank lines

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main()
{
    string line;

    while(getline(cin, line)){
        if(!line.empty()){
            cout << line << endl;
        }
    }

    return 0;
}
