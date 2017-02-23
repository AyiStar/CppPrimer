//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include "../HeadFile/Sales_item.h"
#include <iterator>

int main()
{
    std::istream_iterator<Sales_item> item_iter(std::cin), eof;
    std::ostream_iterator<Sales_item> out_iter(std::cout, "\n");
    
    // store the first transaction in sum and read the next record
    Sales_item sum = *item_iter++;
    while ( item_iter != eof) {
        // if the current transaction (which is stored in item_iter) has the same ISBN
        if (item_iter->isbn() == sum.isbn())
            sum += *item_iter++; // add it to sum and read the next transaction
        else {
            out_iter = sum; // write the current sum
            sum = *item_iter++; // read the next transaction
        }
    }
    out_iter = sum; // remember to print the last set of record
    
    return 0;
}