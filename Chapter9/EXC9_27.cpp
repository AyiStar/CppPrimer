//
// Created by ayistar on 2/14/17.
//

#include <iostream>
#include <forward_list>

int main()
{
    std::forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::forward_list<int>::iterator it = flst.begin(), it_pre = flst.before_begin();
    while(it != flst.end()){
        if(*it % 2){
            it = flst.erase_after(it_pre);
        }
        else{
            ++it;
            ++it_pre;
        }
    }

    for(const auto &i : flst)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}