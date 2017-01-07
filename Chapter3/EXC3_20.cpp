//
// Created by ayistar on 1/7/17.
//

// read a set of integers into a vector
// print the sum of each pair of adjacent elements
// print the sum of the first and last elements,
// followed by the sum of the second and second-to-last, and so on

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    int val = 0;
    vector<int> ivec;

    while(cin >> val){
        ivec.push_back(val);
    }

    for(vector<int>::size_type i = 0
            ; i < ivec.size() - 1; i++){
        cout << ivec[i] + ivec[i + 1];

        if( (i + 1) % 8)
            cout << " ";
        else
            cout << endl;
    }
    cout << endl;

    for(vector<int>::size_type i = 0, j = ivec.size() - 1
            ; i < j; i++, j--){
        cout << ivec[i] + ivec[j];

        if((i + 1) % 8)
            cout << " ";
        else
            cout << endl;
    }
    cout << endl;

    return 0;
}
