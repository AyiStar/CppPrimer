//
// Created by ayistar on 2/22/17.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <list>

int main()
{
    std::vector<int> vec({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::list<int> lst1, lst2, lst3;

    std::copy(vec.cbegin(), vec.cend(), std::inserter(lst1, lst1.end()));
    std::copy(vec.cbegin(), vec.cend(), std::front_inserter(lst2));
    std::copy(vec.cbegin(), vec.cend(), std::back_inserter(lst3));

    for(const auto &i : lst1) std::cout << i << " ";
    std::cout << std::endl;
    for(const auto &i : lst2) std::cout << i << " ";
    std::cout << std::endl;
    for(const auto &i : lst3) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
