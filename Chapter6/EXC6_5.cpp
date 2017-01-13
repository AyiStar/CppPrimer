//
// Created by ayistar on 1/13/17.
//

// write a function to
// return the absolute value of its argument


#include <iostream>
using std::cout;
using std::endl;

int absolute(int x)
{
    return ((x > 0) ? x : -x);
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::cout << absolute(n) << endl;
    
    return 0;
}