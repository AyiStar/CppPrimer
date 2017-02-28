//
// Created by ayistar on 2/28/17.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

int main()
{
    std::map<std::string, std::vector<std::string>> families
            ({ {"Bi", {"Bi Haoyang", "Bi Xiaozhu"}}, 
               {"Zheng", {"Hu Bingyu"}}});
    families["Hu"].push_back("Zheng Ruoxi");
    families["Zhang"].push_back("Zhang Juntao");
    
    for(const auto &pair : families) {
        std::cout << pair.first << " ";
        for(const auto &s : pair.second)
            std::cout << s << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
