//
// Created by ayistar on 2/17/17.
//

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec = {2, 3, 5, 7, 11, 13, 17, 19, 19, 19, 7, 2};
    std::cout << std::count(vec.cbegin(), vec.cend(), 1) 
              << std::count(vec.cbegin(), vec.cend(), 7)
              << std::count(vec.cbegin(), vec.cend(), 19)
              << std::endl;
    return 0;
}
