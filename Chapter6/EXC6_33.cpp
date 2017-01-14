//
// Created by ayistar on 1/14/17.
//

// write a recursive function
// to print the contents of a vector

#include <iostream>
#include <vector>

void PrintVec(std::vector<int>::iterator beg, std::vector<int>::iterator end)
{
    if(beg == end)
        return;
    else{
        std::cout << *beg << std::endl;
        PrintVec(++beg, end);
    }
}


int main()
{
    std::vector<int> v = {2,3,5,7,11,13,17,19};
    PrintVec(v.begin(), v.end());
    return 0;
}