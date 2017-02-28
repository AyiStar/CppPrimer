//
// Created by ayistar on 2/28/17.
//

#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::vector<int> ivec;
    for (std::vector<int>::size_type i = 0; i != 10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    
    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> miset(ivec.cbegin(), ivec.cend());
    std::cout << ivec.size() << std::endl;
    std::cout << iset.size() << std::endl;
    std::cout << miset.size() << std::endl;
    
    return 0;
}
