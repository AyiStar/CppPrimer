//
// Created by ayistar on 2/20/17.
//

#include <iostream>

int main()
{
   int i = 5;
   auto f = [&i] () -> bool { return (i > 0) ? (--i) : i ; };
   while(f())
       std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}
