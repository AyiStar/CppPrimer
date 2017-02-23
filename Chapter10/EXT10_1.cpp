//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include <iterator>

int main()
{
    std::ostream_iterator<int> os(std::cout, "!");
    *os = 1;
    *os = 2;
    *os = 3;
    ++os;
    ++os;
    *os = 4;
    return 0;
}
