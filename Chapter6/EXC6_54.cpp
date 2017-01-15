//
// Created by ayistar on 1/15/17.
//

// write four functions that
// add, subtract, multiply, and divide two int values.
// declare a vector whose elements have these function pointer type
// call each element in the vector and print their result

#include <iostream>
#include <vector>

int add(int x, int y)
{
    return (x + y);
}

int subtract(int x, int y)
{
    return (x - y);
}

int multiply(int x, int y)
{
    return (x * y);
}

int divide(int x, int y)
{
    return (x / y);
}

int main()
{
    std::vector<int (*) (int, int)> v;
    v.push_back(&add);
    v.push_back(&subtract);
    v.push_back(&multiply);
    v.push_back(&divide);
    
    for(int i = 0; i != 4; ++i){
        std::cout << v[i](30,5) << std::endl;
    }
    
    return 0;
}
