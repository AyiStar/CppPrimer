//
// Created by ayistar on 1/7/17.
//

// create a vector with ten int elements.
// using an iterator, assign each element a value
// that is twice its current value.
// test it by printing the vector.

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> v;

    for(int i = 0; i < 9; i++){
        v.push_back(i*i);
        cout << v[i] << " ";
    }
    cout << endl;

    for(auto iter = v.begin();
            iter != v.end(); iter++){
        *iter = (*iter) * 2;
    }

    for(auto iter = v.cbegin();
            iter != v.cend(); iter++){
        cout << *iter << " ";
    }
    cout << endl;

    return 0;


}
