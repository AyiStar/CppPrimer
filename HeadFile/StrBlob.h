//
// Created by ayistar on 3/10/17.
//

#ifndef CPPPRIMER_STRBLOB_H
#define CPPPRIMER_STRBLOB_H

#include <stirng>
#include <vector>
#include <memory>
#include <exception>

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // elements access
    std::string& front();
    std::string& front() const;
    std::string& back();
    std::string& back() const;


private:
    std::shared_ptr<std::vector<std::string>> data;
    // throw msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) { }

StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string>>(il)) { }

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (data->size() <= i)
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::front() const
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}


std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

std::string& StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


#endif //CPPPRIMER_BLOB_H
