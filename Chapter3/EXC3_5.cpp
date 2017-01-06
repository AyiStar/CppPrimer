//
// Created by ayistar on 1/5/17.
//

// read strings from the stdin
// concatenate what is read into one large string
// print the concatenated string
// Then print by separating adjacent input strings by a space

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

int main()
{
    string str_temp, str_sum_1, str_sum_2;
    
    if(cin >> str_temp) {
        str_sum_1 = str_sum_2 = str_temp;
        while (cin >> str_temp) {
            str_sum_1 = str_sum_1 + str_temp;
            str_sum_2 = str_sum_2 + " " + str_temp;
        }
    }
    else{
        cerr << "No input" << endl;
        return -1;
    }
    
    cout << str_sum_1 << endl;
    cout << str_sum_2 << endl;
    
    return 0;
    
}