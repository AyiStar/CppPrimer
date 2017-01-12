//
// Created by ayistar on 1/12/17.
//

// given two vectors of int
// determine whether one vector is a prefix of the other

#include <iostream>
#include <vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    vector<int> ivec1, ivec2;
    int ival = 0;

    while(cin >> ival){
        ivec1.push_back(ival);
    }
    cin.clear();
    while(cin >> ival){
        ivec2.push_back(ival);
    }

    auto iter1 = ivec1.cbegin(), iter2 = ivec2.cbegin();
    while(iter1 != ivec1.cend() && iter2 != ivec2.cend()){
        if(*iter1 != *iter2)
            break;
        ++iter1;
        ++iter2;
    }

    if(iter1 == ivec1.cend()){
        cout << "The first vector is a prefix of the second one" << endl;
    }
    else if(iter2 == ivec2.cend()){
        cout << "The second vector is a prefix of the first one" << endl;
    }
    else{
        cout << "Neither vector is a prefix of the other" << endl;
    }

    return 0;
}
