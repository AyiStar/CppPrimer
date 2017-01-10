//
// Created by ayistar on 1/10/17.
//

// use a conditional operator to find the elements
// in a vector<int> that have odd value
// and double the value of each such element

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> ivec = {0,1,12,123,1234,12345,123456,1234567};

    for(auto &i : ivec){
        i = ((i % 2) ? (2 * i) : i);
    }

    for(auto i : ivec){
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}