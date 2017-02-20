//
// Created by ayistar on 2/19/17.
//

#include <iostream>
#include "../HeadFile/Sales_data.h"
#include <vector>
#include <algorithm>

bool compareIsbn(const Sales_data &item1, const Sales_data &item2)
{
    return item1.isbn() < item2.isbn();
}

int main()
{
    std::vector<Sales_data> vec;
    
    std::string s;
    while(std::cin >> s){
        vec.push_back(Sales_data(s));
    }
    
    std::sort(vec.begin(), vec.end(), compareIsbn);
    for(const auto &item : vec)
        std::cout << item.isbn() << std::endl;
    
    return 0;
}