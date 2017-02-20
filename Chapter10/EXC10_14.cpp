//
// Created by ayistar on 2/20/17.
//

#include <iostream>

int add_9 (int x)
{
    auto sum = [x] (int i) { return x + i; };
    int z = sum(9);
    return z;
}

int main()
{
    std::cout << add_9(18) << std::endl;
    return 0;
}