//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::istream_iterator<int> is(std::cin);
    std::vector<int> vec;
    auto it = std::back_inserter(vec);
    it = *is++;
    it = *is;

    for(const auto &i : vec)
        std::cout<< i << " ";
    std::cout << std::endl;

    return 0;
}
