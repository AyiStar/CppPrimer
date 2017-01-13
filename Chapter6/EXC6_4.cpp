//
// Created by ayistar on 1/13/17.
//

// write a function that
// interacts with the user
// asking for a number
// and generating the factorial of that number

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void interact_fact(void)
{
    int n = 0;
    cout << "Please enter an integer: ";
    cin >> n;
    
    int ret = 1;
    for(int i = 2; i <= n; ++i)
        ret *= i;
    
    cout << "The factorial of " << n << " is " << ret << endl;
    return;
}

int main()
{
    interact_fact();
    return 0;
}
