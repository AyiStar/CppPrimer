//
// Created by ayistar on 2/26/17.
//

#include <iostream>
#include <list>

int main()
{
    std::list<int> lst({2, 2, 2, 3, 3, 5, 2, 2, 3, 3, 5, 5});
    lst.sort();
    lst.unique();
    for(const auto &i : lst)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}
