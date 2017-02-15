//
// Created by ayistar on 2/15/17.
//

#include <iostream>
#include <string>

void replace_instance (const std::string &oldVal, const std::string &newVal, std::string &s)
{
    for(std::string::size_type i = 0; i < s.size(); ++i)
    {
        if(s.substr(i, oldVal.size()) == oldVal)
        {
            s.replace(i, oldVal.size(), newVal);
            i += newVal.size() - 1;
        }
    }

    return;
}

int main()
{
    std::string oldVal("tho"), newVal("though")
        ,s("tho hello tho world\n");
    replace_instance(oldVal, newVal, s);
    std::cout << s << std::endl;
    return 0;
}