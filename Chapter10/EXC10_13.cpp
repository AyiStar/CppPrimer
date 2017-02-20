//
// Created by ayistar on 2/19/17.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

bool isAtLeastFive (const std::string &s)
{
    return s.size() >= 5;
}


int main()
{
    std::vector<std::string> words({"bi", "bibibibi", "hao", "haohaohao", "yang", "yangyangyang"});
    std::partition(words.begin(), words.end(), isAtLeastFive);
    for(const auto &s : words)
        std::cout << s << " ";
    std::cout << std::endl;
    
    return 0;
}