//
// Created by ayistar on 1/10/17.
//

// print the size of each of built-in types

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout    << sizeof(short) << ' ' 
            << sizeof(int) << ' '
            << sizeof(long) << ' '
            << sizeof(float) << ' '
            << sizeof(double) << ' '
            << sizeof(void*) << ' '
            << sizeof(char) << ' '
            << sizeof(bool) << endl;
    
    return 0;
}
