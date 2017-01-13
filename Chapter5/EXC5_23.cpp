//
// Created by ayistar on 1/13/17.
//

// read two integers from the stdin
// print the result of dividing the first number by the second

// throw an exception if the second number is zero.
// test what happens if we don't catch any exception

// use a try block to catch the exception
// the catch clause should print a message to the user
// and ask them to supply a new number
// and repeat the code inside the try

#include <iostream>
#include <stdexcept>
// #define TEST

#ifdef TEST
int main()
{
    int v1 = 0, v2 = 0;

    while(std::cin >> v1 >> v2){
        if(v2 == 0)
            throw std::runtime_error ("Error: can't divide by zero\n");
        std::cout << "The quotient of " << v1 << " and " << v2 << " is " << v1 / v2 << std::endl;
    }

    return 0;
}

#else
int main()
{
    int v1 = 0, v2 = 0;

    while(std::cin >> v1 >> v2){
        try{
            if(v2 == 0)
                throw std::runtime_error ("Error: can't divide by zero\n");
            std::cout << "The quotient of " << v1 << " and " << v2 << " is " << v1 / v2 << std::endl;
        } catch (std::runtime_error div_zero){
            std::cout << div_zero.what() << "Reinput? Enter y or n: ";
            char c;
            std::cin >> c;
            if(!(std::cin) || c == 'n')
                break;
        }
    }

    return 0;
}

#endif