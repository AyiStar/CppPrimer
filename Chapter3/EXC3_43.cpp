//
// Created by ayistar on 1/9/17.
//

// write three different versions of a program to print the element of ia
// 1 - use a range for
// 2 - use an ordinary for with subscripts
// 3 - use an ordinary for with pointers
// write all types directly
// then do them again writing all types using type alias
// then do them again writing all type using auto

#include <iostream>
using std::cout;
using std::endl;
using std::endl;
using std::begin;
using std::end;

int main()
{
    int ia[3][4] = {{1,2,3,4}, {10,20,30,40}, {100,200,300,400}};

    cout << "write types directly" << endl;
    for(int (&row)[4] : ia){
        for(int col : row){
            cout << col << ' ';
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            cout << ia[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    for(int (*prow)[4] = begin(ia); prow != end(ia); prow++){
        for(int *pcol = begin(*prow); pcol != end(*prow); pcol++){
            cout << *pcol << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "using type alias" << endl;
    using int_arr = int[4];
    for(int_arr &row : ia){
        for(int &col : row){
            cout << col << ' ';
        }
        cout << endl;
    }
    cout << endl;

    for(int_arr *prow = begin(ia); prow != end(ia); prow++){
        for(int *pcol = begin(*prow); pcol != end(*prow); pcol++){
            cout << *pcol << ' ';
        }
        cout << endl;
    }
    cout << endl;

    cout << "using auto" << endl;
    for(auto &row : ia){
        for(auto &col : row){
            cout << col << ' ';
        }
        cout << endl;
    }
    cout << endl;

    for(auto prow = begin(ia); prow != end(ia); prow++){
        for(auto pcol = begin(*prow); pcol != end(*prow); pcol++){
            cout << *pcol << ' ';
        }
        cout << endl;
    }

    return 0;

}
