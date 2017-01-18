//
// Created by ayistar on 1/16/17.
//


#ifndef CPPPRIMER_PERSON_H
#define CPPPRIMER_PERSON_H
#define FUNCTIONS

#include <iostream>
#include <string>

class Person {
    friend std::istream &read (std::istream&, Person&);
    friend std::ostream &print (std::ostream&, const Person&);
public:
    Person() = default;
    Person(const std::string &s): name(s){}
    Person(const std::string &nm, const std::string &ad):
        name(nm), address(ad){}
    Person(std::istream &);

    std::string Name() const { return this->name; }
    std::string Address() const { return this->address; }

private:
    std::string name;
    std::string address;
};

std::istream &read (std::istream &is, Person &rhs);
std::ostream &print (std::ostream &os, const Person &rhs);

Person::Person(std::istream &is)
{
    read(is, *this);
}



#ifdef FUNCTIONS

std::istream &read (std::istream &is, Person &rhs)
{
    is >> rhs.name >> rhs.address;
    return is;
}

std::ostream &print (std::ostream &os, const Person &rhs)
{
    os << rhs.Name() << " " << rhs.Address();
    return os;
}



#endif // FUNCTIONS

#endif //CPPPRIMER_PERSON_H
