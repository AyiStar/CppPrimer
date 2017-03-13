//
// Created by ayistar on 3/13/17.
//

#include <iostream>
#include <vector>
#include <memory>

std::vector<int>*
func1 (){
    std::vector<int>* p = new std::vector<int>();
    return p;
}

std::vector<int>*
use_func1(){
    std::vector<int>* p = func1();
    int i = 0;
    while (std::cin >> i)
        p->push_back(i);
    std::cin.clear();
    return p;
}

void
print_func1(){
    std::vector<int>* p = use_func1();
    for (const auto &i : *p)
        std::cout << i << " ";
    std::cout << std::endl;
    delete p;
    return;
}

std::shared_ptr<std::vector<int>>
func2 (){
    std::shared_ptr<std::vector<int>> p = std::make_shared<std::vector<int>> ();
    return p;
}

std::shared_ptr<std::vector<int>>
use_func2(){
    std::shared_ptr<std::vector<int>> p = func2();
    int i = 0;
    while (std::cin >> i)
        p->push_back(i);
    std::cin.clear();
    return p;
}

void
print_func2(){
    std::shared_ptr<std::vector<int>> p = use_func2();
    int i = 0;
    for (const auto &i : *p)
        std::cout << i << " ";
    std::cout << std::endl;
    return;
}


int main()
{
    print_func1();
    print_func2();
    return 0;
}
