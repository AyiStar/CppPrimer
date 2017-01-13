//
// Created by ayistar on 1/13/17.
//

// using pointers, write a function
// to swap the values of two ints.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void Swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
    
    return;
}

int main()
{
    int x = 2, y = 3;
    Swap(&x, &y);
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    
    return 0;
}
