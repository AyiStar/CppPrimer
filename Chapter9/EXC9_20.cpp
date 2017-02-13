//
// Created by ayistar on 2/13/17.
//


#include <iostream>
#include <list>
#include <deque>

int main()
{
    std::list<int> l = {0, 1, 2, 3, 4, 5, 15, 16, 17, 18};
    std::deque<int> q1, q2;

    for(const auto &i : l){
        if(i % 2)
            q1.push_back(i);
        else
            q2.push_back(i);
    }

    for(const auto &i : q1)
        std::cout << i << " ";
    std::cout << std::endl;

    for(const auto &i : q2)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}