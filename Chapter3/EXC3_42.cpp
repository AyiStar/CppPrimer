//
// Created by ayistar on 1/9/17.
//

// copy a vector of ints into an array of ints

#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> ivec = {2,3,5,7,11,13,17,19,23,29};
    int arr[10] = {0};

    // copy all the elements of ivec into arr
    auto iter1 = ivec.cbegin();
    auto iter2 = std::begin(arr);
    while(iter2 != std::end(arr) && iter1 != ivec.cend()){
        *iter2 = *iter1;
        iter1++;
        iter2++;
    }

    for(iter2 = std::begin(arr); iter2 != std::end(arr); iter2++){
        cout << *iter2<< " ";
    }
    cout << endl;

    return 0;
}
