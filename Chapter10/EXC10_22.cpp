//
// Created by ayistar on 2/21/17.
//

#include <iostream>
#include <functional>

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() <= sz;
}

int main()
{
    std::string s({"Ha"});
    auto check3 = std::bind(check_size, std::placeholders::_1, 3);
    std::cout << check3(s) << std::endl;
    return 0;

}