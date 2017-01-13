//
// Created by ayistar on 1/13/17.
//

// write a function that returns 0 when it is first called
// and then generates numbers in sequence each time it is called again.

#include <iostream>
using std::cout;
using std::endl;

size_t count_calls()
{
    static size_t cnt= 0;
    return cnt++;
}

int main()
{
    for(int i = 0; i < 10; i++)
        cout << count_calls() << endl;
    
    return 0;
}
