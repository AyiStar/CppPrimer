//
// Created by ayistar on 2/24/17.
//

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main()
{
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::vector<int> vec;
    
    while(in_iter != eof)
    {
        vec.push_back(*in_iter++);
    }
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), out_iter);
    
    return 0;
}
