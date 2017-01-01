//
// Created by ayistar on 12/31/16.
//

// read data from stdin into a Sales_item
// and write that Sales_item to back on the stdout

#include <iostream>
#include "../HeadFile/Sales_item.h"

int main()
{
    Sales_item book;

    // read ISBN, number of copies, and sales price
    std::cin >> book;

    //write ISBN, number of copies, and sales price
    std::cout << book <<  std::endl;

    return 0;
}
