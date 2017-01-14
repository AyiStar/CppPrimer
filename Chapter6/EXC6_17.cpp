//
// Created by ayistar on 1/14/17.
//

// write a function to determine
// whether a string contains any capital letters

// write a function to change a string to all lowercase

#include <iostream>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;

bool AnyCapital(const string &s)
{
    for(auto c : s){
        if(isupper((int)c))
            return true;
    }
    return false;
}

void GetLowercase(string &s)
{
    for (auto &c : s){
        c = tolower(c);
    }
    return;
}

int main()
{
    string s;
    cin >> s;
    cout << "There are " << (AnyCapital(s) ? "" : "no") << " capital characters" << endl;
    GetLowercase(s);
    cout << s << endl;
    return 0;
}
