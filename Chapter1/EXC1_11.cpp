//
// Created by ayistar on 12/30/16.
//

//print numbers in the range of two numbers
//not use if-statement

#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;

    std::cout << "Enter two numbers: " << std::endl;
    std::cin >> v1 >> v2;

    int i = v1;
    while(i <= v2)
    {
        std::cout << i << " ";
        i++;
    }

    i = v1;
    while(i >= v2)
    {
        std::cout << i << " ";
        i--;
    }

    std::cout << std::endl;

    return 0;
}
