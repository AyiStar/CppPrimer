//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include <numeric>
#include <iterator>


int main()
{
    std::istream_iterator<int> in(std::cin), eof;
    std::cout << std::accumulate(in, eof, 0) << std::endl;
    return 0;
}

