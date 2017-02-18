//
// Created by ayistar on 2/18/17.
//


#include <iostream>
#include <algorithm>
#include <vector>

void delete_duplicates(std::vector<int> &v)
{
    std::sort(v.begin(), v.end());
    auto end_unique = std::unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
    return;
}

int main()
{
    std::vector<int> v({1, 5, 9, 2, 4, 3, 3, 3, 2, 2, 10, 1, 100});
    delete_duplicates(v);
    for(const auto &i : v){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}