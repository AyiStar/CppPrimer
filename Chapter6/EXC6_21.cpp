//
// Created by ayistar on 1/14/17.
//

// write a function that
// takes an int and a pointer to an int
// and returns the larger of the int value or the value to which the pointer points

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int Compare(const int x, const int *py)
{
    return (x > *py) ? x : *py;
}

int main()
{
    int x = 2, y = 3;
    cout << Compare(x, &y) << endl;

    return 0;
}
