//
// Created by ayistar on 2/14/17.
//

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> ivec;
    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    for(std::vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);

    std::cout << "ivec: size: " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    int i = 0;
    while(ivec.size() != ivec.capacity()){
        ivec.push_back(i++);
    }

    std::cout << i << std::endl;

    return 0;
}
