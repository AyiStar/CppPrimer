//
// Created by ayistar on 1/22/17.
//

#include <iostream>
#include <sstream>

std::istream &repeat(std::istream &is)
{
    char c;
    while(is >> c){
        std::cout << c;
    }
    is.clear();
    return is;
}

int main()
{
    std::string s("Hello, world!\n");
    std::istringstream isstrm(s);
    repeat(isstrm);
    repeat(isstrm);
    return 0;
}