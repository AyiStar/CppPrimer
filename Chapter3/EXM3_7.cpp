//
// Created by ayistar on 1/7/17.
//

// count the number of grades
// by clusters of ten

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<unsigned> scores(11,0);
    unsigned grade;
    while(cin >> grade){
        if(grade <= 100){
            ++ scores[grade / 10];
        }
    }
    return 0;
}