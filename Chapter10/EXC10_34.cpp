//
// Created by ayistar on 2/24/17.
//

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec = {2, 3, 5, 7, 11, 13, 17, 19};

    for(auto rit = vec.rbegin(); rit != vec.crend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;

    auto it = --vec.end();
    while(it != vec.begin())
    {
        std::cout << *it << " ";
        --it;
    }
    std::cout << *it << std::endl;

    std::for_each(vec.rbegin(), vec.rend(),
                  [] (const int & i)
                  { std::cout << i << " "; });
    std::cout << std::endl;

    return 0;
}
