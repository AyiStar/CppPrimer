//
// Created by ayistar on 2/20/17.
//


#include <iostream>
#include <algorithm>
#include "../HeadFile/Sales_data.h"
#include <vector>

int main()
{
    std::vector<Sales_data> vec;
    std::string s;
    while(std::cin >> s){
        vec.push_back(Sales_data(s));
    }
    std::sort(vec.begin(), vec.end(), 
              [](const Sales_data &a, const Sales_data &b) 
              { return a.isbn() < b.isbn();});
    for(const auto &item : vec)
    {
        std::cout << item.isbn() << std::endl;
    }
    return 0;
}