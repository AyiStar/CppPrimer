//
// Created by ayistar on 12/30/16.
//

//add unknown number of integers

#include <iostream>

int main()
{
    int sum = 0, value = 0;

    while(std::cin >> value)
    {
        sum += value;
    }

    std::cout << "Sum is " << sum << std::endl;
    return 0;
}