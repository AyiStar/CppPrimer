//
// Created by ayistar on 1/13/17.
//

// write a fact function

#include <iostream>

int fact(int n)
{
    int ret = 1;
    while(n){
        ret *= n;
        --n;
    }

    return ret;
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::cout << fact(n) << std::endl;

    return 0;
}
