//
// Created by ayistar on 1/14/17.
//

// write a main function that
// takes several arguments
// print the values of the arguments
// concatenate the supplied arguments and print the resulting string


#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    string s;
    for(int i = 1; i < argc; ++i){
        s += argv[i];
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }
    cout << s << endl;
    return 0;
}