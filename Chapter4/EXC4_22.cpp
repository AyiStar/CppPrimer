//
// Created by ayistar on 1/10/17.
//

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;


int main()
{
    string s;
    int grade = 0;
    
    while(cin >> grade){
        s = (grade > 90) ? "high pass" : (grade > 75) ? "good pass" : (grade > 60) ? "pass" : "fail";
        cout << s << endl;
        if(grade > 90)
            s = "high pass";
        else if(grade > 75)
            s = "good pass";
        else if(grade > 60)
            s = "pass";
        else
            s = "fail";
        
        cout << s << endl;
    }
    return 0;
}
