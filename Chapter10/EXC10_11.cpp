//
// Created by ayistar on 2/19/17.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


void elimDups(std::vector<std::string> &v)
{
    std::sort(v.begin(), v.end());
    auto end_unique = std::unique(v.begin(), v.end());
    v.erase(end_unique, v.end());
    return;
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

int main()
{
    std::vector<std::string> vec({"bi", "hao", "yang", "hu", "bing", "yu", "bi", "hao", "yang", "Bi", "Hao", "Yang"});
    elimDups(vec);
    std::stable_sort(vec.begin(), vec.end(), isShorter);
    
    for(const auto &s : vec)
        std::cout << s << " ";
    std::cout << std::endl;
    
    return 0;
}
