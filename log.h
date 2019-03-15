#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <iostream>
#include <string>

#include "aliases.h"


namespace mylogger {

template<class T>
void log(const T& str)
{
    std::cout << "Log: " << std::to_string(str) << std::endl;
}


// TODO для массивов написать int[]
template<class T>
void log(const T* str)
{
    std::cout << "Log: " << str << std::endl;
}


//template<class T>
//inline void log(T ch)
//{
//    std::cout << "Log: " << ch << std::endl;
//}


template<>
inline void log<std::string>(const std::string& str)
{
    std::cout << "Log: " << str << std::endl;
}






template<class T>
void log(const std::string& prefix, const T& str)
{
    std::cout << "Log: " << prefix <<  std::to_string(str) << std::endl;
}


template<class T>
void log(const std::string& prefix, const T* str)
{
    std::cout << "Log: " << prefix << str << std::endl;
}


template<>
inline void log<std::string>(const std::string& prefix, const std::string& str)
{
    std::cout << "Log: " << prefix << str << std::endl;
}

} // end "namespace mylogger"


#endif // LOG_H_INCLUDED
