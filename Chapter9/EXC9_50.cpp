//
// Created by ayistar on 2/15/17.
//

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> vsint = {"1", "12", "123", "2345" };
    std::vector<std::string> vsdouble = {"1.5", "2.5", "3.5"};
    
    int intsum = 0;
    double doublesum = 0;
    
    for(const auto &s : vsint){
        intsum += stoi(s);
    }
    for(const auto &s : vsdouble){
        doublesum += stod(s);
    }
    
    std::cout << intsum << " " << doublesum << std::endl;
    return 0;
}
