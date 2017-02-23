//
// Created by ayistar on 2/23/17.
//

#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>

int main()
{
    std::ifstream file("EXC10_29_txt_file");
    if(!file.is_open()){
        std::cout << "can't open file" << std::endl;
        return -1;
    }

    std::istream_iterator<std::string> is_it(file), eof;
    std::vector<std::string> vec;
    auto insert_it = std::back_inserter(vec);
    while(is_it != eof){
        insert_it = *is_it++;
    }

    for(const auto &s : vec)
        std::cout << s << std::endl;

    return 0;
}
