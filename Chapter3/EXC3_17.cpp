//
// Created by ayistar on 1/7/17.
//

// read a sequence of words from cin
// and store the values in a vector
// then, process the vector and change each word to uppercase
// print the transformed elements, eight words to a line

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
    string str;
    vector<string> svec;

    while(cin >> str){
        svec.push_back(str);
    }

    for(auto &s : svec){
        for(auto &c : s){
            c = toupper(c);
        }
    }

    for(vector<string>::size_type i = 0
            ; i < svec.size(); i++ ){
        cout << svec[i];

        if((i+1) % 8)
            cout << " ";
        else
            cout << endl;
    }
    cout << endl;

    return 0;
}
