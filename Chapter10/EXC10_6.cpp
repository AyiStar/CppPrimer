//
// Created by ayistar on 2/18/17.
//


#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    std::list<int> lst({2, 3, 5, 7, 11, 13, 17, 19});
    std::fill_n(lst.begin(), lst.size(), 0);

    for(const auto &i : lst)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}