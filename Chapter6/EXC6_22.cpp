//
// Created by ayistar on 1/14/17.
//

// write a function to swap two int pointers

#include <iostream>

void Swap(int *&px, int *&py)
{
    int *temp = px;
    px = py;
    py = temp;
    
    return;
}

int main()
{
    int x = 2, y = 3;
    int *px = &x, *py = &y;
    Swap(px, py);
    std::cout << *px << ' ' << *py << std::endl;
    
    return 0;
}
