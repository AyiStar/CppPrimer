//
// Created by ayistar on 2/8/17.
//


#include <iostream>
#include <vector>

std::vector<int>::iterator
find(std::vector<int>::iterator begin, std::vector<int>::iterator end,
 int value)
{
    while(begin != end){
        if(*begin == value)
            return begin;
        ++begin;
    }
    return end;
}

int main()
{
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    std::vector<int>::iterator iter;
    
    iter = find(v.begin(), v.end(), 4);
    if(iter != v.end())
        std::cout << "found" << std::endl;
    else
        std::cout << "couldn't find" << std::endl;
    
    return 0;
}