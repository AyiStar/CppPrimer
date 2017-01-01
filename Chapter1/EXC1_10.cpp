//
// Created by ayistar on 12/30/16.
//

//print the numbers from ten down to zero

#include <iostream>

int main()
{
    int i = 10;

    while(i >= 0)
    {
        std::cout << i << " " ;
        --i;
    }
    std::cout << std::endl;

    return 0;
}

