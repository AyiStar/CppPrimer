//
// Created by ayistar on 1/4/17.
//

// add two Sales_data objects

#include <iostream>
#include <string>
#include "../HeadFile/Sales_data.h"

int main()
{
    Sales_data data1, data2;

    // code to read into data1 and data2
    double price = 0.0;
    std::cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = data1.units_sold * price;
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;

    // code to check whether data1 and data2 have the same ISBN
    // and if so, print the sum of data1 and data2
    if(data1.bookNo == data2.bookNo){
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        std::cout << data1.bookNo << " " << totalCnt
                  << " " << totalRevenue << " ";
        if(totalCnt > 0){
            std::cout << totalRevenue / totalCnt << std::endl;
        }
        else{
            std::cout << "(no sales)" << std::endl;
        }
        return 0;
    }
    else{
        std::cerr << "Data must refer to the same ISBN" << std::endl;
        return  -1;
    }

}
