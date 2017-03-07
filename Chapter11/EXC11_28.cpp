//
// Created by ayistar on 3/7/17.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>


int main()
{
    std::map<std::string, std::vector<int>> m({ {"Bihaoyang", {2, 3, 5}},
                                               {"Hubingyu", {7, 11, 13}}
                                              });
    std::map<std::string, std::vector<int>>::iterator ret = m.find("Bihaoyang");

    if(ret != m.end())
        std::cout << ret->first << std::endl;
    else
        std::cout << "Not found" << std::endl;

    return 0;
}
