//
// Created by ayistar on 2/12/17.
//

// assign the elements from a list of char* pointers to C-style character stings
// to a vector of strings

#include <iostream>
#include <vector>
#include <list>

int main()
{
    std::list<char*> l = {"Hello", "World", "!"};
    std::vector<std::string> v = {"Bi", "Hao", "Yang", "Love", "Hu", "Bing", "Yu"};
    
    v.assign(l.cbegin(), l.cend());
    for(const auto &s : v){
        std::cout << s + " ";
    }
    std::cout << std::endl;
    return 0;
}

