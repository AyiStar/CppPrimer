//
// Created by ayistar on 1/16/17.
//


#ifndef CPPPRIMER_PERSON_H
#define CPPPRIMER_PERSON_H
#define FUNCTIONS

class Person {
    std::string name() const { return name; }
    std::string address() const { return address; }

    std::string name;
    std::string address;
};



#ifdef FUNCTIONS

std::istream &read (std::istream &is, Person &rhs)
{
    is >> rhs.name >> rhs.address;
    return is;
}

std::ostream &print (std::ostream &os, const Person &rhs)
{
    os << rhs.name() << " " << rhs.address();
    return os;
}



#endif

#endif //CPPPRIMER_PERSON_H
