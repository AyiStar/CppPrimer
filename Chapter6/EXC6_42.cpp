//
// Created by ayistar on 1/14/17.
//

// give the second parameter of make_plural a default argument of 's'

#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

string make_plural (size_t ctr, const string &word, const string &end = "s")
{
    if(ctr > 1)
        return (word + end);
    else
        return word;
}

int main()
{
    string s = "pig";
    size_t cnt = 5;
    
    cout << make_plural(cnt, s);
    
    return 0;
}
