//
// Created by ayistar on 2/20/17.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> vec;
    std::string s;
    
    while(std::cin >> s)
    {
        vec.push_back(s);
    }
    std::cin.clear();
    
    int length = 0;
    std::cin >> length;
    auto count = std::count_if(vec.begin(), vec.end(),
                          [length] (const std::string &s)
                          { return s.size() >= length; });
    std::cout << count << " word(s) equal or longer than " 
              << length << std::endl;
    return 0;
}
