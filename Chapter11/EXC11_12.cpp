//
// Created by ayistar on 2/28/17.
//

#include <iostream>
#include <vector>
#include <utility>
#include <string>

int main()
{
    std::vector<std::pair<std::string, int>> vec;
    std::string s;
    int i;

    while (std::cin >> s >> i){
        vec.push_back(std::make_pair(s, i));
    }
    
    for(const auto & p : vec){
        std::cout << p.first << " " << p.second << std::endl;
    }
    
    return 0;
}
