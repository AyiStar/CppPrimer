//
// Created by ayistar on 12/31/16.
//

// read several transactions and
// counts how many transactions occur for each ISBN

#include <iostream>
#include "../HeadFile/Sales_item.h"

int main()
{
    Sales_item book, currBook;
    int cnt = 1;

    if(std::cin >> book)
    {
        while(std::cin >> currBook){
            if(currBook.isbn() == book.isbn()){
                ++cnt;
            }
            else{
                std::cout << book.isbn() << " occurs " << cnt << " times "
                          << std::endl;
                cnt = 1;
                book = currBook;
            }
        }
    }
    else
    {
        std::cerr << "No data" << std::endl;
        return -1;
    }

    std::cout << book.isbn() << " occurs " << cnt << " times "
              << std::endl;

    return 0;

}
