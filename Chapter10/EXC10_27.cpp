//
// Created by ayistar on 2/22/17.
//


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

int main()
{
    // for simplicity, already sorted
    std::vector<int> vec({2, 3, 3, 4, 5, 6, 6, 6, 7, 8, 8, 8, 9, 10});
    std::list<int> lst;
    std::unique_copy(vec.begin(), vec.end(), std::back_inserter(lst));

    for(const auto &i : lst)
    std::cout << i << std::endl;

    return 0;
}