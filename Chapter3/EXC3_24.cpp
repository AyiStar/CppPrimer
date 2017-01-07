//
// Created by ayistar on 1/7/17.
//

// read a set of integers into a vector
// print the sum of each pair of adjacent elements
// print the sum of the first and last elements,
// followed by the sum of the second and second-to-last, and so on
// using iterators

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> v;
    int val;

    while(cin >> val){
        v.push_back(val);
    }

    for(auto iter = v.cbegin(); iter < v.cend() - 1; iter++){
        cout << (*iter) + *(iter + 1) << " ";
    }
    cout << endl;

    for(auto iter1 = v.cbegin(), iter2 = v.cend() - 1;
            iter1 < iter2; iter1++, iter2--){
        cout << *iter1 + *iter2 << " ";
    }
    cout << endl;

    return 0;
}
