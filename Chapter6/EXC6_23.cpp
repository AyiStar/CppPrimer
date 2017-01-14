//
// Created by ayistar on 1/14/17.
//

// write print functions
// each of these functions print i and j defined as followed
// int i = 0, j[2] = {0,1}

#include <iostream>
using std::cout;
using std::endl;

void PrintInt(const int &i)
{
    cout << i << endl;
    return;
}

void PrintArray_v1(const int *beg, const int *end)
{
    while(beg != end){
        cout << *beg << endl;
        ++beg;
    }
    return;
}

void PrintArray_v2(const int arr[], const size_t size)
{
    for(size_t i = 0; i < size; ++i){
        cout << arr[i] << endl;
    }
    return;
}

int main()
{
    int i = 0, j[2] = {0,1};
    PrintInt(i);
    PrintArray_v1(std::begin(j), std::end(j));
    PrintArray_v2(j, 2);
    return 0;
}