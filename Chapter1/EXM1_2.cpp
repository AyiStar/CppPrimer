//
// Created by ayistar on 12/30/16.
//

//sum the numbers form 1 through 10 inclusive

#include <iostream>

int main()
{
    int sum = 0, val = 1;

    while(val <= 10)
    {
        sum += val;
        ++val;
    }

    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    return 0;
}