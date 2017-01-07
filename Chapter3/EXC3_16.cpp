//
// Created by ayistar on 1/7/17.
//

// print the size and contents of the vectors from exercise 3.13

#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10,42);
    vector<int> v4{10};
    vector<int> v5{10,42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    cout << "The size of vectors:" << endl;
    cout << v1.size() << " " << v2.size() << " " << v3.size() << " " << v4.size() << " "
         << v5.size() << " " << v6.size() << " " << v7.size() << endl;

    cout << "The contents of vectors:" << endl;
    for(auto c : v1){
        cout << c << " ";
    }
    cout << endl;

    for(auto c : v2){
        cout << c << " ";
    }
    cout << endl;
    for(auto c : v3){
        cout << c << " ";
    }
    cout << endl;

    for(auto c : v4){
        cout << c << " ";
    }
    cout << endl;

    for(auto c : v5){
        cout << c << " ";
    }
    cout << endl;

    for(auto c : v6){
        cout << c << " ";
    }
    cout << endl;

    for(auto c : v7){
        cout << c << " ";
    }
    cout << endl;

    return 0;
}

