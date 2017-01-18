//
// Created by ayistar on 1/17/17.
//

#include "../HeadFile/Person.h"
#include <iostream>
#include <string>


int main()
{
    Person p1;
    Person p2("Bihaoyang", "China");
    Person p3("Bihaoyang");
    Person p4(std::cin);

    print(std::cout, p1) << std::endl;
    print(std::cout, p2) << std::endl;
    print(std::cout, p3) << std::endl;
    print(std::cout, p4) << std::endl;

    return 0;
}
