//
// Created by ayistar on 1/14/17.
//

// write a function that
// takes an initializer_list<int>
// and produces the sum of the elements

#include <iostream>
#include <initializer_list>


int Sum(std::initializer_list<int> int_list)
{
    int sum = 0;
    for(auto val : int_list)
        sum += val;
    return sum;
}

int main()
{
    std::cout << Sum({1,2,3,4,5,6,7,8}) << std::endl;
    return 0;
}
