//
// Created by ayistar on 2/15/17.
//

#include <iostream>
#include <string>

int main()
{
    std::string s("ab2c3d7R4E6");
    std::string number("0123456789");
    std::string alpha;
    
    for(std::size_t t = 0; t < 26; ++t) {
        alpha.push_back('a' + t);
        alpha.push_back('A' + t);
    }
    std::string::size_type pos = 0;
    while((pos = s.find_first_of(number, pos)) != std::string::npos){
        std::cout << s[pos] << " ";
        ++pos;
    }
    std::cout << std::endl;
    
    pos = 0;
    while((pos = s.find_first_of(alpha, pos)) != std::string::npos){
        std::cout << s[pos] << " ";
        ++pos;
    }
    std::cout << std::endl;
    
    return 0;
}
