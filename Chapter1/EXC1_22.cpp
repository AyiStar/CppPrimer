//
// Created by ayistar on 12/31/16.
//

// read unknown number of transactions for the same ISBN
// write the sum of all the transactions that were read

#include <iostream>
#include "../HeadFile/Sales_item.h"

int main()
{
    Sales_item currBook, sumBook;

    if(std::cin >> sumBook){
        while(std::cin >> currBook){
            if(currBook.isbn() == sumBook.isbn()){
                sumBook += currBook;
            }
            else{
                std::cerr << "Different ISBN" << std::endl;
            }
        } // end while
    }
    else{
        std::cerr << "No data" << std::endl;
        return -1;
    }

    std::cout << sumBook << std::endl;

    return 0;
}
