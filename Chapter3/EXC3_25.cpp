//
// Created by ayistar on 1/7/17.
//

// rewrite the grade clustering program
// using iterators

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<unsigned> cluster(10,0);
    unsigned grade = 0;
    auto iter = cluster.begin();

    while(cin >> grade){
        if(grade <= 100){
            (*(iter + (grade / 10)))++;
        }
    }

    for(iter = cluster.begin(); iter < cluster.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}
