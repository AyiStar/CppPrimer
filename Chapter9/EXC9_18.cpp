//
// Created by ayistar on 2/13/17.
//

#include <iostream>
#include <deque>
#include <string>
#include <list>

int main()
{
    std::deque<std::string> q;
    std::list<std::string> l;
    std::string s;
    
    std::cout << "Write to the deque" << std::endl;
    while(std::cin >> s)
        q.push_back(s);
    
    for(const auto &s : q)
        std::cout << s << " ";
    std::cout << std::endl;
    
    std::cin.clear();
    std::cout << "Write to the list" << std::endl;
    while(std::cin >>s)
        l.push_back(s);
    
    for(const auto &s : l)
        std::cout << s << " ";
    std::cout << std::endl;
    
    return 0;
}