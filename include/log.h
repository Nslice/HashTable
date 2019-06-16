#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

#include "include/aliases.h"



class Logger
{
private:
    std::ofstream fout;  //TODO вывод в файл

public:
    void operator()(const std::string& str)
    {
        std::cout << str << std::endl;
    }


    void operator()(const std::string& prefix, const std::string& str)
    {
        std::cout << "__" << prefix << ": " << str << std::endl;
    }


    void operator()(const std::string& str, std::ofstream& os)
    {
        os << str << std::endl;
    }


    template<typename T>
    void operator()(const T* ar, uint size)
    {
        if (size > 0)
        {
            std::cout << "[" << ar[0];
            for (uint i = 1; i < size; i++)
                std::cout << ", " << ar[i];
            std::cout << "]";
        }
        std::cout << std::endl;
    }


} extern logger;


#endif // LOGGER_H_INCLUDED
