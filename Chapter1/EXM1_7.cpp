//
// Created by ayistar on 1/1/17.
//

// read a file of sales transactions
// produce a report that shows
// for each book
// the total number of copies sold, the total revenue
// and the average sales price
// assume that all the transactions for each ISBN 
// are grouped together in the input

#include <iostream>
#include "../HeadFile/Sales_item.h"

int main()
{
    Sales_item total;
    
    if(std::cin >> total){
        Sales_item trans;
        while(std::cin >> trans){
            if(total.isbn() == trans.isbn()){
                total += trans;
            }
            else{
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std::endl;
    }
    else{
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}
