//
// Created by ayistar on 2/21/17.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() < sz;
}

int main()
{
    std::vector<int> vec({2, 3, 1, 5, 7, 5, 6, 8, 10});
    std::string s("Bihaoyang");
    auto checkValue = std::bind(check_size, s, std::placeholders::_1);
    auto it = std::find_if(vec.begin(), vec.end(), checkValue);
    std::cout << *it << std::endl;
    return 0;
}