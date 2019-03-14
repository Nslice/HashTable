#ifndef ILIST_H_INCLUDED
#define ILIST_H_INCLUDED

#include <list>
#include <iostream>

template<typename T>
class IList
{
public:
    virtual ~IList(){}

//    void push_back(const T& obj) = 0;
//    void push_front(const T& obj) = 0;

//    void pop_back() = 0;
//    virtual void pop_front() = 0;

};





template<typename T>
class TempList :  public std::list<T>, public IList<T>
{
public:

//    virtual ~TempList() override;

};






#endif // ILIST_H_INCLUDED
