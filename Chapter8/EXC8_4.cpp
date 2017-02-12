//
// Created by ayistar on 1/26/17.
//


// write a function to open a file for input
// and read its contents into a vector of strings,
// storing each line as a separate element in the vector

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> &
read(const std::string file_name, std::vector<std::string> &v)
{
    std::ifstream input(file_name);
    if (!input){
        std::cerr << "error: can't open " << file_name << std::endl;
        return v;
    }

    v = {};
    std::string s;
    while(std::getline(input, s)){
        v.push_back(s);
    }

    return v;

}

std::ofstream &
write(std::ofstream &output, const std::string &file_name, const std::vector<std::string> &v)
{
    output.open(file_name, std::ofstream::app);
    if(!output){
        std::cerr << "error: can't open " << file_name << std::endl;
    }
    for (const auto &s : v){
        output << s << std::endl;
    }
    output.close();
    return output;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        std::cerr << "Error: wrong argument" << std::endl;
        return -1;
    }

    std::vector<std::string> v;
    read(argv[1], v);

    std::ofstream output;
    write(output, argv[2], v);
    write(output, argv[2], v);

    v = {};
    read(argv[2], v);

    for(const auto &s : v)
    {
        std::cout << s << std::endl;
    }

    return 0;
}
