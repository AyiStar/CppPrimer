//
// Created by ayistar on 1/22/17.
//

#include <iostream>

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
    repeat(std::cin);
    repeat(std::cin);
    return 0;
}