//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include <vector>
#include <iterator>

int main()
{
    std::vector<int> vec({2, 3, 5, 7, 11, 13});
    std::ostream_iterator<int> out_iter(std::cout, " ");
    for(const auto &e : vec)
        *out_iter++ = e;
    std::cout << std::endl;
    return 0;
}
