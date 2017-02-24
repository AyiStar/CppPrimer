//
// Created by ayistar on 2/24/17.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include "../HeadFile/Sales_item.h"

int main()
{
    std::vector<Sales_item> vec;

    Sales_item item;
    while(std::cin >> item)
    {
        vec.push_back(item);
    }

    std::sort(vec.begin(), vec.end(),
              [] (const Sales_item &item1, const Sales_item &item2)
              { return item1.isbn() < item2.isbn(); });

    auto it1 = vec.begin(), it2 = vec.end();
    while(it1 != it2)
    {
        auto it3 = std::find_if(it1, it2,
                             [it1] (const Sales_item &tmp)
                             { return tmp.isbn() != it1->isbn(); });
        auto sum = std::accumulate(it1, it3, Sales_item(it1->isbn()));
        std::cout << sum << std::endl;
        it1 = it3;
    }

    return 0;
}