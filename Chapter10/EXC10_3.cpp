//
// Created by ayistar on 2/18/17.
//

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v({2, 3, 5, 7, 11, 13});
    int sum = std::accumulate(v.cbegin(), v.cend(), 0);
    std::cout << sum << std::endl;
    
    return 0;
}
