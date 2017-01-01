//
// Created by ayistar on 12/31/16.
//

//own version of a program that
//prints the sum of a set of integers read from cin

#include <iostream>

int main()
{
    int sum = 0, val = 0;

    for(sum = 0; std::cin >> val; sum += val)
        ;

    std::cout << "The sum is " << sum << std::endl;
    return 0;
}
