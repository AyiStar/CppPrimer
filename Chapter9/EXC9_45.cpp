//
// Created by ayistar on 2/15/17.
//

#include <iostream>
#include <string>

void add_prefix(const std::string &prefix, std::string &name)
{
    name.insert(name.begin(), prefix.begin(), prefix.end());
    return;
}

void add_suffix(const std::string &suffix, std::string &name)
{
    name.append(suffix);
    return;
}

int main()
{
    std::string name = "Pig";
    add_prefix("Mr. ", name);
    add_suffix(" III", name);
    std::cout << name << std::endl;
    return 0;
}
