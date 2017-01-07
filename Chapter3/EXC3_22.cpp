//
// Created by ayistar on 1/7/17.
//

// print each line in text up to the first blank line
// then change the elements in text
// that correspond to the first paragraph to all uppercase

#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<string> text;
    string buf;
    
    while(std::getline(cin, buf)){
        text.push_back(buf);
    }
    
    for(auto iter = text.cbegin();
        iter != text.cend() && !(iter->empty());
        iter++){
        cout << *iter << endl;
    }
    
    for(auto iter = text.begin(); 
            iter != text.end() && !(iter->empty());
            iter++){
        for(auto &c : *iter){
            c = toupper(c);
        }
    }
    
    for(auto iter = text.cbegin();
            iter != text.cend() && !(iter->empty());
            iter++){
        cout << *iter << endl;
    }
    
    return 0;
}